/*
 * thread.c
 *
 *  Created on: 29 Mar 2023
 *      Author: mabecker
 */
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>
#include "thread.h"
#include "time_funcs.h"
#include "aps.h"
#include "trace.h"
#include "logConf.h"

#ifdef PRINT_THREAD_INFO_MSG
  #define THREAD_PRINT_INFO( fmt, ...) fprintf( stdout, "[THREAD] " fmt "\r\n", ##__VA_ARGS__)
#else
  #define THREAD_PRINT_INFO(fmt, ...)
#endif


#ifdef PRINT_THREAD_ERROR_MSG
  #define THREAD_PRINT_ERROR( fmt, ...) fprintf( stdout, "[THREAD ERROR]" fmt " [%s:%d]\r\n", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
  #define THREAD_PRINT_ERROR( fmt, ...)
#endif

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/**
 * Start of the linked list with all thread information
 */
struct thread_data* threads;

/**
 * Number of threads
 */
int thread_count = 0;

/**
 * Helper function to print the time values in us nicely
 */
void prettyPrintMs(uint64_t value) {
	uint64_t ms = value / 1000000;

	printf("%5d ms", ms);
}

/**
 * Returns the pointer to the thread list
 */
struct thread_data*  thread_getThreadPointer() {
	return threads;
}

/**
 * Function to register a thread description to the system
 */
struct thread_data* thread_addThreadDescription(char* _name, int _period_ms, int _deadline_ms, int _offset_us, int _priority, unsigned _core_affinity, int _aps_partition) {
	struct thread_data* list_pointer = threads;

	assert(_period_ms < 1000);							// Should be changed below to properly configure the seconds as well
	assert(_deadline_ms <= _period_ms);					// Only implicit deadlines are supported
	assert(_offset_us < 1000000);						// Should be changed below to properly configure the seconds as well
	assert(_priority > 0 && _priority <= 255);			// Make sure the priority is in the allowed range

	struct thread_data* new_thread = malloc(sizeof(struct thread_data));
	if (new_thread != NULL) {
		new_thread->period.tv_sec = 0;
		new_thread->period.tv_nsec = PERIOD_IN_NANOS(_period_ms);
		new_thread->deadline.tv_sec = 0;
		new_thread->deadline.tv_nsec = PERIOD_IN_NANOS(_deadline_ms);
		new_thread->offset.tv_sec = 0;
		new_thread->offset.tv_nsec = _offset_us * 1000UL;
		new_thread->priority = _priority;
		new_thread->core_affinity = _core_affinity;
		new_thread->partition_id = _aps_partition;
		new_thread->name = _name;
		new_thread->thread_code = thread_baseTaskCode;
		new_thread->terminate = false;

		if (_period_ms == -1) new_thread->sporadic = true;

		// get the end of the list of threads
		if (list_pointer == NULL) {
			threads = new_thread;
		} else {
			while (list_pointer->next != NULL) {
				list_pointer = list_pointer->next;
			}
			list_pointer->next = new_thread;
		}

		thread_count++;

		return new_thread;

	} else {
		THREAD_PRINT_ERROR("Could not create new thread (%s, %d)", __FILE__, __LINE__);
		return NULL;
	}
}

/**
 * Function adds a runnable to a task. The task is identified by name,
 */
void thread_registerRunnable(char* _name, runnable_spec_t* _runnable_spec) {
	struct thread_data* thread = thread_getThread(_name);

	if (thread != NULL) {
		if (thread->runnable == NULL) {
			thread->runnable = _runnable_spec;
		} else {
			runnable_spec_t* tmpRunnable = thread->runnable;
			while (tmpRunnable->next != NULL) {
				tmpRunnable = tmpRunnable->next;	// Find the end of the runnable list
			}

			tmpRunnable->next = _runnable_spec;		// Add the new runnable at the end of the list
		}
	} else {
		THREAD_PRINT_ERROR("Could not find thread to register new runnable.");
	}
}

void thread_configureStrictPriorities() {
	struct sched_config sched_data;

	memset(&sched_data, 0, sizeof(sched_data));

	/**
	 * The priority threshold above which a thread always displaces a lower-priority thread running on the CPU on which it becomes ready.
	 */
	sched_data.low_latency_priority = 0;

	/**
	 * The priority threshold above which a preempted thread will be rescheduled on another CPU (the one running the lowest-priority thread).
	 */
	sched_data.migrate_priority = 0;

	int ret = SchedCtl( SCHED_CONFIGURE, &sched_data, sizeof(sched_data));
	if (ret != EOK) {
		THREAD_PRINT_ERROR("Couldn't configure scheduler  %s (%d).", strerror(errno), errno);
	} else {
		THREAD_PRINT_INFO("Configured scheduler to work as strict fixed priority.");
	}
}

void thread_releaseCondition(){
	THREAD_PRINT_INFO("Now releasing all threads");
	set_common_release();	//set the time all threads start executing
	TRACE_THREAD_RELEASE_JOBS();
	pthread_cond_broadcast(&cond);
}

int thread_setThreadParameters(int policy, int priority, int tid) {
	struct sched_param param;
	int retcode;
	/* Get the scheduling parameters. */
	retcode = pthread_getschedparam(pthread_self(), &policy, &param);
	if (retcode != EOK) {
		THREAD_PRINT_ERROR ("pthread_getschedparam: %s.\n", strerror (retcode));
		return -1;
	}
	param.sched_priority = priority;
	retcode = pthread_setschedparam( pthread_self(), policy, &param);
	if (retcode != EOK) {
		THREAD_PRINT_ERROR ("pthread_setschedparam: %s.\n", strerror (retcode));
		return -1;
	}
	return 0;
}

/**
 * This function creates all defined threads.
 */
void thread_createThreads(){
	pthread_attr_t my_attr;
	pthread_attr_init(&my_attr);
	pthread_attr_setinheritsched(&my_attr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&my_attr, SCHED_FIFO);
	struct sched_param param;

	struct thread_data* list_pointer = threads;

	if (list_pointer != NULL) {
		do {
			param.sched_priority = list_pointer->priority;
			pthread_attr_setschedparam(&my_attr, &param);
			pthread_create(&list_pointer->thread_id, &my_attr, list_pointer->thread_code, (void *) list_pointer);

			list_pointer = list_pointer->next;

		} while (list_pointer != NULL);
	}

	sleep(1);
	return;
}

int thread_setAffinity(int numCores, unsigned coreBitmap) {
	void *my_data;

	/* Determine the number of array elements required to hold
	 * the runmasks, based on the number of CPUs in the system. */
	unsigned num_elements = RMSK_SIZE(_syspage_ptr->num_cpu);

	/* Determine the size of the runmask, in bytes. */
	int masksize_bytes = num_elements * sizeof(unsigned);

	/* Allocate memory for the data structure that we'll pass
	 * to ThreadCtl(). We need space for an integer (the number
	 * of elements in each mask array) and the two masks
	 * (runmask and inherit mask). */
	int size = sizeof(int) + 2 * masksize_bytes;
	if ((my_data = malloc(size)) == NULL) {
		THREAD_PRINT_ERROR("Malloc unsuccessful.");
		return 1;
	} else {
		memset(my_data, 0x00, size);

		// Set up pointers to the "members" of the structure.
		unsigned* rsizep = (unsigned *)my_data;
		unsigned *rmaskp = rsizep + 1;
		unsigned *imaskp = rmaskp + num_elements;

		// Set the size.
		*rsizep = num_elements;

		for (int c = 0; c < numCores; ++c) {
			unsigned cpu = 1 << c;
			if ((coreBitmap & cpu) == cpu) {
				// Set the runmask. Call this macro once for each processor	the thread can run on.
				RMSK_SET(c, rmaskp);

				// Set the inherit mask. Call this macro once for each processor the thread's children can run on.
				RMSK_SET(c, imaskp);
			} else {
				RMSK_CLR(c, rmaskp);
				RMSK_CLR(c, imaskp);
			}
		}
		if ( ThreadCtl( _NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT,	my_data) == -1) {
			THREAD_PRINT_ERROR("Could not set thread affinity.");
			return 1;
		}
		return 0;
	}
}

/**
 * Helper function to print a formatted table with the task set information
 */
void thread_printInfo() {
	struct thread_data* list_pointer = threads;

	printf("\n------------------------------------------------------------------------\n");
	printf("| Name                      | Period    | Priority  | Partition | Core \n");
	printf("------------------------------------------------------------------------\n");

	if (list_pointer != NULL) {
		do {
			printf("| %25s |", list_pointer->name);

			if (list_pointer->period.tv_nsec >= 0) {
				printf(" %4d ms   |", (list_pointer->period.tv_nsec / 1000000UL));
			} else {
				printf("   -- ms   |");
			}

			printf("%3d       | P_%d       |", list_pointer->priority, list_pointer->partition_id);

			if ((list_pointer->core_affinity & 1) != 0) printf(" CORE_0 ");
			if ((list_pointer->core_affinity & 2) != 0) printf(" CORE_1 ");
			if ((list_pointer->core_affinity & 4) != 0) printf(" CORE_2 ");
			if ((list_pointer->core_affinity & 8) != 0) printf(" CORE_3 ");
			printf("\r\n");
			//thread_traceThreadParameters(list_pointer);



			list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	} else {
		printf("list pointer is NULL\r\n");
	}

	printf("------------------------------------------------------------------------\n\n");
}

/**
 * Function handles the end of a job's execution
 */
void thread_jobEnd(struct thread_data* thread) {

	/* Boost the threads priority temporarily so all semaphores can be posted in one go. */
	pthread_setschedprio(pthread_self(), 255);

	thread->current_job_id++;	// Advance the job count in preparation of the next job

	// Record the response time of this instance
	// For time triggered threads, the current_activation time is set based on the period.
	uint64_t responsetime_ns = get_time_since_ns(&thread->current_activation, CLOCK_MONOTONIC) + 1000000;	// adding one ms since the timer granularity is 1ms
	stat_new_value(&thread->responseTime_ns, responsetime_ns);

	//printf("%s %" PRIu64 " %" PRIu64 "\n", thread->name, responsetime_ns, time_in_ns(&thread->deadline));
	if (responsetime_ns > time_in_ns(&thread->deadline)) {	// Check if the deadline is violated
		thread->deadlineViolations++;
	}


	// Compute the next activation time
	timespec_add(&thread->current_activation, &thread->period, &thread->current_activation);

	// Record the execution time of the job
	uint64_t exec_ns = (get_time_now_ns(thread->cid) - thread->execStart_ns);// + 1000000;	// adding one ms since the timer granularity is 1ms
	//printf("%s %" PRIu64 "\n", thread->name, exec_ns);
	stat_new_value(&thread->execTime_ns, exec_ns);

	stat_new_value(&thread->deadline_ns, time_in_ns(&thread->deadline));

	thread_saveRecord(thread, exec_ns, responsetime_ns, time_in_ns(&thread->deadline));

	// Log the end time of this job's execution
	TRACE_THREAD_JOB_END(thread);

	/* Return to the threads nominal priority. */
	pthread_setschedprio(pthread_self(), thread->priority);
}

/**
 * Function to send user events via the QNX tracing facility that describe the threads we created.
 * This is used to help the trace evaluation.
 */
void thread_traceThreadParameters(struct thread_data* thread) {
	char id_buffer[20];

	TRACE_REG_PERIOD(thread, (thread->period.tv_nsec / 1000000UL));
	TRACE_REG_PRIORITY(thread);
	sprintf(id_buffer, " %i %s ", thread->thread_id, thread->name);
	TRACE_REG_NAME(id_buffer);

}

/**
 * Wait for all application threads to terminate.
 * Called from the main function.
 */
void thread_joinThreads() {
	struct thread_data* list_pointer = threads;

	THREAD_PRINT_INFO("Waiting for user threads to finish");
	if (list_pointer != NULL) {
		do {
		pthread_join(list_pointer->thread_id, NULL);

		list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	}
	THREAD_PRINT_INFO("All user threads finished");
	return;
}

/**
 * Send the signal SIGUSR1 to all application threads.
 * This will unblock currently blocked threads. The signal handler will
 * additionally set 'terminate' to true which will cause threads to exit.
 */
void thread_killThreads() {
	struct thread_data* list_pointer = threads;

	THREAD_PRINT_INFO("Terminating all threads");
	if (list_pointer != NULL) {
		do {

			/**
			 * Send the signal SIGUSR1 to each application thread. This will unblock threads that are waiting for
			 * semaphores as well as currently sleeping threads. The signal handler will set the atomic variable
			 * 'terminate' to indicate that the thread should finish execution.
			 */
			atomic_store_explicit(&list_pointer->terminate, true, memory_order_seq_cst);//test
			pthread_kill(list_pointer->thread_id, SIGUSR1);

		list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	}
	return;
}



/**
 * Enables cancellation points for a thread and sets the cancellation type to deferred.
 */
void thread_setCancelation() {
	int err;

	err = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if (err != EOK) {
		THREAD_PRINT_ERROR("Can't set cancellation state: %s", strerror(err));
	}

	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	if (err != EOK) {
		THREAD_PRINT_ERROR("Can't set cancellation type: %s", strerror(err));
	}
}

/**
 * Signal handler called once pthread_kill sends SIGUSR1 to an application thread.
 */
void thread_signalHandler(int signum) {
	if (signum == SIGUSR1) {
		struct thread_data* list_pointer = threads;
		pthread_t id = pthread_self();

		if (list_pointer != NULL) {
			do {

				if (list_pointer->thread_id == id) {
					atomic_store_explicit(&list_pointer->terminate, true, memory_order_seq_cst);
				}

			list_pointer = list_pointer->next;
			} while (list_pointer != NULL);
		}
	}
}

/**
 * Function prints the runtime statistics for all threads
 */
void thread_printStatistics() {
	struct thread_data* list_pointer = threads;

	printf("-----------------------------------------------------------------------------------------------------------\n");
	printf("| Name                      |  Min RT |  Max RT | Avrg RT |  Min ET |  Max ET | Avrg ET |   Jobs | DlMiss |\n");
	printf("-----------------------------------------------------------------------------------------------------------\n");

	if (list_pointer != NULL) {
		do {
			printf("| %25s | ", list_pointer->name);

			prettyPrintMs(list_pointer->responseTime_ns.min);
			printf("| ");
			prettyPrintMs(list_pointer->responseTime_ns.max);
			printf("| ");
			prettyPrintMs(list_pointer->responseTime_ns.avrg);
			printf("| ");
			prettyPrintMs(list_pointer->execTime_ns.min);
			printf("| ");
			prettyPrintMs(list_pointer->execTime_ns.max);
			printf("| ");
			prettyPrintMs(list_pointer->execTime_ns.avrg);
			printf("|");
			printf(" %6d ", list_pointer->current_job_id - 1);
			printf("| %6d |\r\n", list_pointer->deadlineViolations);


			list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	} else {
		printf("list pointer is NULL\r\n");
	}

	printf("-----------------------------------------------------------------------------------------------------------\n");
}

/**
 * Get a pointer to the thread data of the thread with the given name.
 */
struct thread_data* thread_getThread(char* name) {
	struct thread_data* list_pointer = threads;

	while (list_pointer != NULL) {

		if (strcmp(list_pointer->name, name) == 0) {
			return list_pointer;
		}
		list_pointer = list_pointer->next;
	}

	return NULL;
}

/**
 * Get a pointer to the thread data from a given thread ID
 */
struct thread_data* thread_getThreadFromId(int tid) {
	struct thread_data* list_pointer = threads;

	while (list_pointer != NULL) {

		if (list_pointer->thread_id == tid) {
			return list_pointer;
		}
		list_pointer = list_pointer->next;
	}

	return NULL;
}

/**
 * Base thread to implement the skeleton for all threads in the framework.
 */
void* thread_baseTaskCode(void * arg) {

	struct thread_data *ps = (struct thread_data *) arg;
	ps->current_job_id = 1;

	/**
	 * Initialize thread parameters
	 */
	thread_setCancelation();																// Enable cancellation points for this thread and set to deferred.
	pthread_getcpuclockid(pthread_self(), &ps->cid);										// Get the clock-id of the thread. This is used to simulate execution cycles of the runnables and to record worst-observed execution times.
	ps->runnable->cid = ps->cid;															// Also set the cid for the runnable
	thread_setAffinity(4, ps->core_affinity);												// Map the thread to a core.
	pthread_setschedprio(pthread_self(), ps->priority);										// Assign a fixed priority to the thread.
//	aps_joinPartition(ps->partition_id, pthread_self());									// Assign the thread to an APS partition

	/**
	 * Wait for synchronous release (with possible offset)
	 */
	pthread_mutex_lock(&mutex);
	printf("[Thread %d] Waiting for release\n", ps->thread_id);
	pthread_cond_wait(&cond, &mutex);														// Make sure all threads are ready
	pthread_mutex_unlock(&mutex); 															// Unlocking for all other threads
	ps->current_activation = *get_common_release_time();									// Get the common release time of all threads on this node
	timespec_add(&ps->current_activation, &ps->current_activation, &ps->offset);			// add the possible offset the first job of the thread should be released

	/*****************************************************************
	 * Periodic part of the thread
	 *****************************************************************/
	while (atomic_load_explicit(&ps->terminate, memory_order_seq_cst) != true) {


		if (sleep_until_next_activation(ps)) {											// Wait until the next job is released

			TRACE_THREAD_JOB_START(ps);													// Log the start time of this job's execution

			thread_runnable_read(ps);													// Execute the READ sections of all runnable's

			thread_runnable_execute(ps);												// Execute the EXECUTE sections of all runnable's

			thread_runnable_write(ps);													// Execute the WRITE sections of all runnable's

			thread_jobEnd(ps);															// Log the response time and set the next release.
		}
	}

	return(EXIT_SUCCESS);
}

/**
 * Create copies of all input labels for all runnables of the thread
 */
void thread_runnable_read(struct thread_data* ps) {

	runnable_spec_t* tmpRunnable = ps->runnable;

	do {
		for (int i = 0; i < tmpRunnable->inputLabelCount; i++) {								// Copy all input labels
			label_read(tmpRunnable->inputLabelIds[i], tmpRunnable->inputData[i]);
		}

		tmpRunnable = tmpRunnable->next;
	} while (tmpRunnable != NULL);
}

/**
 * Call the runnable code for all runnables of the thread. At this point all input data is already copied
 */
void thread_runnable_execute(struct thread_data* ps) {

	runnable_spec_t* tmpRunnable = ps->runnable;

	do {
		tmpRunnable->func(tmpRunnable);														// Execute the workload

		tmpRunnable = tmpRunnable->next;
	} while (tmpRunnable != NULL);
}

/**
 * Write all output labels for all runnables of the thread
 */
void thread_runnable_write(struct thread_data* ps) {

	runnable_spec_t* tmpRunnable = ps->runnable;

	do {
		for (int i = 0; i < ps->runnable->outputLabelCount; i++) {
			label_write(ps->runnable->outputLabelIds[i], ps->runnable->outputData[i]);			// Write all output labels
		}

		tmpRunnable = tmpRunnable->next;
	} while (tmpRunnable != NULL);
}

/**
 * Save the runtime measurements to a dedicated file for later usage.
 */
void thread_saveAllMeasurements() {
	struct thread_data* list_pointer = threads;

	THREAD_PRINT_INFO("Save all measurement data.");
	if (list_pointer != NULL) {
		do {

			thread_saveMeasurementFiles(list_pointer);

			list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	}
}

/**
 * Function to create a csv-file with all execution times and response times recorded for a thread.
 */
void thread_saveMeasurementFiles(struct thread_data* thread) {

	char filename[50];
	sprintf(filename, "/dev/shmem/%s_data.csv", thread->name);	// Get the file name

	// open the file for writing
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		THREAD_PRINT_ERROR("Error opening the file %s", filename);
		return;
	}

	for (int i = 0; i < thread->recordPos; i++) {
		fprintf(fp, "%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 "\n", thread->records[i].timestamp, thread->records[i].execTime, thread->records[i].responseTime, thread->records[i].deadline);
	}

	// close the file
	fclose(fp);

}

/**
 * Add a runtime measurement record.
 */
void thread_saveRecord(struct thread_data* thread, uint64_t execTime, uint64_t rt, uint64_t deadline) {
	struct timespec walltime;

	clock_gettime(CLOCK_MONOTONIC, &walltime);

	if (thread->recordPos < MAX_RECORDS) {
		thread->records[thread->recordPos].timestamp = timespec2nsec(&walltime);
		thread->records[thread->recordPos].execTime = execTime;
		thread->records[thread->recordPos].responseTime = rt;
		thread->records[thread->recordPos].deadline = deadline;

		thread->recordPos++;
	}
}

/**
 * Function calls the initialization function of each runnable of each task.
 */
void thread_initRunnables() {
	struct thread_data* list_pointer = threads;

	THREAD_PRINT_INFO("Initialize all runnables.");
	if (list_pointer != NULL) {
		do {

			runnable_spec_t* runnable = list_pointer->runnable;

			// Iterate over all runnables of the thread
			do {

				if (runnable->init != NULL) {
					runnable->init(runnable);
				}

				runnable = runnable->next;
			} while (runnable != NULL);

			list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	}
}

/**
 * Function calls the deinitialization function of each runnable of each task.
 */
void thread_deinitRunnables() {
	struct thread_data* list_pointer = threads;

	THREAD_PRINT_INFO("Deinitialize all runnables.");
	if (list_pointer != NULL) {
		do {

			runnable_spec_t* runnable = list_pointer->runnable;

			// Iterate over all runnables of the thread
			do {

				if (runnable->deinit != NULL) {
					runnable->deinit(runnable);
				}

				runnable = runnable->next;
			} while (runnable != NULL);

			list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	}
}
