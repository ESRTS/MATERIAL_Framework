/*
 * time_funcs.h
 *
 *  Created on: 29 Mar 2023
 *      Author: mabecker
 */

#ifndef TIME_FUNCS_H_
#define TIME_FUNCS_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <signal.h>
#include <sys/siginfo.h>
#include <assert.h>
#include <sys/netmgr.h>
#include <stdbool.h>

#include "thread.h"

#define GIGACYCLES 1000000000
#define MEGACYCLES 1000000
#define KILOCYCLES 1000

/**
 * Enable this to use the assembly loop instead of polling the threads clock.
 */
#define BUSY_LOOP

/**
 * Define the execution time overhead in nano seconds that is subtracted from the WCET to not
 * execute too long.
 *
 * 80000
 */
#define EXECUTION_OVERHEAD_NS 50000

static inline void timespec_add (struct timespec *sum, const struct timespec *left, const struct timespec *right)
{
  sum->tv_sec = left->tv_sec + right->tv_sec;
  sum->tv_nsec = left->tv_nsec + right->tv_nsec;
  if (sum->tv_nsec >= 1000000000)
    {
      ++sum->tv_sec;
      sum->tv_nsec -= 1000000000;
    }
}

static inline int timespec_less_then (const struct timespec *a, const struct timespec *b)
{
	if (a->tv_sec < b->tv_sec) return 1;
	if (a->tv_sec > b->tv_sec) return 0;
	if (a->tv_nsec < b->tv_nsec) return 1;
	return 0;
}

uint64_t get_cycles_per_second();
void timespec_add_ms(struct timespec *t, long ms);
void error_out(char *msg, int error);
void nanospin_clock(unsigned nsec, int cid);
void burn_cycles(int exec_time_ms, int cid);
void burn_cyclesRand(int execTimeInUs, double variation, int cid);
void pclock(char *msg, clockid_t cid);
void compute_diff_time(struct timespec *start, struct timespec *stop, struct timespec *diff);
bool sleep_until_next_activation(struct thread_data *tsk);
void set_common_release();
struct timespec* get_common_release_time();
uint64_t get_time_since_ns(struct timespec *start, clockid_t cid);
void sleepDuration(struct timespec* duration);
void millis_to_timespec(struct timespec *time, int millis);
void getCurrentTime(struct timespec *start);
uint64_t get_time_now_ns(clockid_t cid);
bool timespec_greater_than(struct timespec ts1, struct timespec ts2);
uint64_t time_in_ns(struct timespec* _time);
void ns_to_timespec(struct timespec* _time, uint64_t _time_ns);

#endif /* TIME_FUNCS_H_ */
