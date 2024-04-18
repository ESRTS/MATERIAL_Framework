/*
 * time_funcs.c
 *
 *  Created on: 29 Mar 2023
 *      Author: mabecker
 */
#include "time_funcs.h"
#include "logConf.h"

#define CYCLES_PER_LOOP 3

#define WAIT_CYCLES(X) uint32_t l = X/CYCLES_PER_LOOP;\
asm volatile( "0:" "SUBS %[count], 1;" "BNE 0b;" :[count]"+r"(l) );

#ifdef PRINT_TIME_INFO_MSG
  #define TIME_PRINT_INFO( fmt, ...) fprintf( stdout, "[TIME] " fmt "\r\n", ##__VA_ARGS__)
#else
  #define TIME_PRINT_INFO(fmt, ...)
#endif


#ifdef PRINT_TIME_ERROR_MSG
  #define TIME_PRINT_ERROR( fmt, ...) fprintf( stdout, "[TIME ERROR]" fmt " [%s:%d]\r\n", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
  #define TIME_PRINT_ERROR( fmt, ...)
#endif

/**
 * Holds the common release time of all threads
 */
struct timespec common_release;

void timespec_add_ms(struct timespec *t, long ms)
{
	t->tv_nsec += ms * MEGACYCLES;
	if (t->tv_nsec > GIGACYCLES) {
		t->tv_nsec = t->tv_nsec - GIGACYCLES;// + ms*1000000;
		t->tv_sec += 1;
	}
}

uint64_t get_cycles_per_second(){
	uint64_t cps;
	cps = SYSPAGE_ENTRY(qtime)->cycles_per_sec;
	return cps;
}


/* print error and exit */
void error_out(char *msg, int error) {
	printf("cpu_burner: %s, errno %d:%s\n", msg, error, strerror(error));
	exit(0);
}

/*Burn cycles for specified nanoseconds*/
/* takes care of preemptions because it checks the exact time the thread with clock cid actually ran **/

void nanospin_clock(unsigned nsec, int cid) {
	struct timespec tstart, tnow, tdiff;
	if (clock_gettime(cid, &tstart) == -1) {
		TIME_PRINT_ERROR("error: clock_gettime tstart");
	}
	while (1) {
		if (clock_gettime(cid, &tnow) == -1) {
			TIME_PRINT_ERROR("error: clock_gettime tnow");
		}
		compute_diff_time(&tstart, &tnow, &tdiff);

		if (timespec_less_then(&tnow, &tstart)) return; /* wrapped, might happen on SH */
		if(tdiff.tv_nsec > nsec) return;
	}

}

/*Specify value in useconds*/
void burn_cycles(int execTimeInUs, int cid) {
#ifdef BUSY_LOOP
	execTimeInUs = execTimeInUs * 130;//135;
	uint32_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
	while(execTimeInUs--) {
		asm ("orr %0, %0, %0" : "=r" (a) : "r" (a));
		asm ("add %0, %0, %0" : "=r" (b) : "r" (b));
		asm ("and %0, %0, %0" : "=r" (c) : "r" (c));
		asm ("mov %0, %0" : "=r" (d) : "r" (d));
		asm ("orr %0, %0, %0" : "=r" (e) : "r" (e));
		asm ("add %0, %0, %0" : "=r" (f) : "r" (f));
		asm ("and %0, %0, %0" : "=r" (g) : "r" (g));
		asm ("mov %0, %0" : "=r" (h) : "r" (h));
	}
#else
	unsigned wait_in_ns = execTimeInUs * 1000;	//us to ns

	//if (wait_in_ns <= EXECUTION_OVERHEAD_NS) wait_in_ns = EXECUTION_OVERHEAD_NS + 1000;	// in case the specified value is smaller than the overheads, at least wait 1 us.

	if ((wait_in_ns - EXECUTION_OVERHEAD_NS) > 0) {	// make sure to not send negative values to nanospin_clock
		nanospin_clock(wait_in_ns - EXECUTION_OVERHEAD_NS, cid);
	}
#endif
}

/**
 * Burns CPU cycles for the specified duration [us].
 * The parameter 'variation' allows to specify an additional uncertainty in the execution time
 * which results in waiting times with a variation of +/- (variation * execTimeInUs) from the
 * base value.
 */
void burn_cyclesRand(int execTimeInUs, double variation, int cid) {
	unsigned et_in_ns = execTimeInUs * 1000;
	unsigned change = (unsigned)(et_in_ns * variation);

	unsigned wait_in_ns = et_in_ns - change + (random() % (2 * change));

	//printf("%d\r\n", wait_in_ns);
	nanospin_clock(wait_in_ns - EXECUTION_OVERHEAD_NS, cid);
}

void pclock(char *msg, clockid_t cid)
{
	struct timespec ts;
	printf("%s", msg);
	if (clock_gettime(cid, &ts) == -1)
		TIME_PRINT_ERROR("clock_gettime");
	//printf("%4ld.%03ld\n", ts.tv_sec, ts.tv_nsec / 1000000);
	TIME_PRINT_INFO("thread: %d,  %4ld seconds  %03ld ms\n", pthread_self(), ts.tv_sec, ts.tv_nsec/1000000);
}



void compute_diff_time(struct timespec *start, struct timespec *stop, struct timespec *diff) {
	if(stop ->tv_nsec < start->tv_nsec) {
		diff->tv_nsec =  stop->tv_nsec + GIGACYCLES - start->tv_nsec;
		diff->tv_sec = stop->tv_sec - 1 - start->tv_sec;
	} else {
		diff->tv_nsec =  stop->tv_nsec - start->tv_nsec;
		diff->tv_sec = stop->tv_sec - start->tv_sec;
	}
	return;
}

// Wait until it’s time for the next “job” of the task
// Returns true if successful. If interrupted it returns false;
bool sleep_until_next_activation(struct thread_data *tsk) {
	int err;

	if (tsk->sporadic != true) {

		//printf("Thread_%d going to sleep until %ds %dns\r\n", tsk->thread_id, tsk->current_activation.tv_sec, tsk->current_activation.tv_nsec);
		err = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tsk->current_activation, NULL);
		if (err != 0) {
			if (err == EINTR){
				TIME_PRINT_INFO("Sleep till next activation got interrupted.");
				return false;
			}
		}

	}
	tsk->execStart_ns = get_time_now_ns(tsk->cid);	// Record the time of the local clock at start of the job. This is used to measure execution times

	return true;
}

// wait for a specified interval
void sleepDuration(struct timespec* duration) {
	int err;
	TIME_PRINT_INFO("Sleep for %lld.%.9ld seconds", (long long)duration->tv_sec, duration->tv_nsec);
	do {
		err = clock_nanosleep(CLOCK_MONOTONIC, 0, duration, NULL);
	} while (err != 0 && errno == EINTR);
	assert(err == 0);
}

// set the time all jobs see as the initial release. This is currently 500ms after all threads are released in order to give enough time for each
// thread to execute the initialization code.
void set_common_release() {
	struct timespec release_delay;
	release_delay.tv_sec = 0;
	release_delay.tv_nsec = 500000000;

	int err = clock_gettime(CLOCK_MONOTONIC, &common_release);
	assert(err == 0);

	timespec_add(&common_release, &common_release, &release_delay);
}

// returns the common release time of all threads
struct timespec* get_common_release_time() {
	return &common_release;
}

/**
 * Returns the time (in ns) since a given start time.
 */
uint64_t get_time_since_ns(struct timespec *start, clockid_t cid) {
	struct timespec now;
	struct timespec diff;
	uint64_t diff_ns = 0;

	if (clock_gettime(CLOCK_MONOTONIC, &now) != -1) {
		compute_diff_time(start, &now, &diff);

		diff_ns = diff.tv_nsec + (diff.tv_sec * 1000000000);
	} else {
		TIME_PRINT_ERROR("During call to clock_gettime! (%s, %d)\r\n", __FILE__, __LINE__);
		TIME_PRINT_ERROR("ERRNO: %d (%s)\n", errno, strerror(errno));
	}

	return diff_ns;
}

/**
 * Return the currnent time of the clock in ns
 */
uint64_t get_time_now_ns(clockid_t cid) {
	struct timespec now;
	if (clock_gettime(cid, &now) != -1) {
		return now.tv_nsec + (now.tv_sec * 1000000000);
	} else {
		TIME_PRINT_ERROR("During call to clock_gettime! (%s, %d)\r\n", __FILE__, __LINE__);
		TIME_PRINT_ERROR("ERRNO: %d (%s)\n", errno, strerror(errno));
	}
	return 0;
}

void getCurrentTime(struct timespec *start) {
	if (clock_gettime(CLOCK_MONOTONIC, start) == -1) {
		TIME_PRINT_ERROR("During call to clock_gettime! (%s, %d)\r\n", __FILE__, __LINE__);
		TIME_PRINT_ERROR("ERRNO: %d (%s)\n", errno, strerror(errno));
	}
}

void millis_to_timespec(struct timespec *time, int millis) {
	int seconds = millis / 1000;
	int rest_millis = millis % 1000;

	time->tv_sec = seconds;
	time->tv_nsec = PERIOD_IN_NANOS(rest_millis);
}

bool timespec_greater_than(struct timespec ts1, struct timespec ts2) {
	return (ts1.tv_sec > ts2.tv_sec || (ts1.tv_sec == ts2.tv_sec && ts1.tv_nsec > ts2.tv_nsec));
}

uint64_t time_in_ns(struct timespec* _time) {
	return (_time->tv_sec * 1000000000) + _time->tv_nsec;
}

void ns_to_timespec(struct timespec* _time, uint64_t _time_ns) {
	_time->tv_sec = _time_ns % 1000000000;
	_time->tv_nsec = _time_ns - (1000000000 * _time->tv_sec);
}
