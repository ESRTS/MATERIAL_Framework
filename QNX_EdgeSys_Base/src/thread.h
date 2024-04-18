/*
 * thread.h
 *
 *  Created on: 29 Mar 2023
 *      Author: mabecker
 */

#ifndef THREAD_H_
#define THREAD_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <signal.h>
#include <sys/siginfo.h>
#include <assert.h>
#include <sys/netmgr.h>
#include <sys/time.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdbool.h>
#include "runnable.h"
#include "stat.h"

#define PERIOD_IN_NANOS(X) (X * 1000000UL)
#define MSEC_TO_USEC(X) (X * 1000UL)
#define USEC_TO_NANOS(X) (X * 1000UL)

#define __PULSE_CODE_PRECEDENCE _PULSE_CODE_MINAVAIL

#define MAX_RECORDS 3000

typedef struct {
	uint64_t timestamp;
	uint64_t execTime;
	uint64_t responseTime;
	uint64_t deadline;
} record_t;

/**
 * Function pointer type used for threads
 */
typedef void* (*thread_func_pointer)(void*);

/**
 * Data structure to describe a thread
 */
struct thread_data {

	// thread id as assigned by QNX
	int thread_id;

	// name of the thread
	char* name;

	// desired separation of consecutive activations
	struct timespec period;

	// desired deadline of the thread
	struct timespec deadline;

	// desired offset for this thread
	struct timespec offset;

	// indicate if a thread is sporadic
	bool sporadic;

	// priority of the thread
	int priority;

	// core affinity of this thread
	unsigned core_affinity;

	// pointer to the function that represents the task
	thread_func_pointer thread_code;

	// APS partition id for this thread to run in
	int partition_id;

	// just for convenience, we keep track of the
	// sequence number of the current job
	unsigned long current_job_id;

	// time at which the current instance was (supposed
	// to be) activated
	struct timespec current_activation;

	// flag to let applications terminate themselves
	atomic_bool terminate;

	// total time to run this task before it exits
	struct timespec total_runtime;

	// Used to describe execution characteristics. Possibly a list of runnables.
	runnable_spec_t* runnable;

	// CPU clock ID of this thread
	clockid_t cid;

	/*------------------------------------------------------------------
	 * Used for track runtime statistics
	 *----------------------------------------------------------------*/

	// Statistics for the observed execution time
	stat_t execTime_ns;

	// Statistics for the response time
	stat_t responseTime_ns;

	// Log threads deadline
	stat_t deadline_ns;

	// Time of the threads core clock at start of execution
	uint64_t execStart_ns;

	// Record the number of observed deadline violations
	uint32_t deadlineViolations;

	record_t records[MAX_RECORDS];

	int recordPos;

	// pointer to the next thread in the list
	struct thread_data* next;
};

struct thread_data* thread_addThreadDescription(
		char* _name,
		int _period_ms,
		int _deadline_ms,
		int _offset_us,
		int _priority,
		unsigned _core_affinity,
		int _aps_partition);
void thread_registerRunnable(char* _name, runnable_spec_t* _runnable_spec);
struct thread_data*  thread_getThreadPointer();
void thread_releaseCondition();
void thread_configureStrictPriorities();
int thread_setThreadParameters(int policy, int priority, int tid);
void thread_killThreads();
void thread_joinThreads();
void thread_createThreads();
int thread_setAffinity(int numCores, unsigned coreBitmap);
void thread_printInfo();
void thread_traceThreadParameters(struct thread_data* thread);
void thread_setCancelation();
void thread_signalHandler(int signum);
void thread_printStatistics();
struct thread_data* thread_getThread(char* name);
void thread_jobEnd(struct thread_data* thread);
void thread_runnable_read(struct thread_data* ps);
void thread_runnable_execute(struct thread_data* ps);
void thread_runnable_write(struct thread_data* ps);
void* thread_baseTaskCode(void * arg);
struct thread_data* thread_getThreadFromId(int tid);
void thread_saveMeasurementFiles(struct thread_data* thread);
void thread_saveAllMeasurements();
void thread_saveRecord(struct thread_data* thread, uint64_t execTime, uint64_t rt, uint64_t deadline);
void thread_initRunnables();
void thread_deinitRunnables();

#endif /* THREAD_H_ */
