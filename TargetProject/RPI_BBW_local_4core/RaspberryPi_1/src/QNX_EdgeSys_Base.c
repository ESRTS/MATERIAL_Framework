#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include "labels.h"
#include "thread.h"
#include "aps.h"
#include "labels_conf.h"
#include "user_runnables.h"
#include "sysConfig.h"
#include "trace.h"
#include "time_funcs.h"
#include "channel.h"

/**
 * Program name for logging
 */
char* progName;

/**
 * Struct indicating the experiment runtime
 */
struct timespec total_runtime;

struct timespec comInit_delay;

/**
 * Signal handler for the application.
 * We catch SIGUSR1 which we use to interrupt blocking syscalls of the threads at shutdown
 */
void signalHandler(int signum) {
	thread_signalHandler(signum);
}

int main(int argc, char **argv) {

	signal(SIGUSR1,signalHandler);

	aps_configureWindowSize(APS_WINDOW_SIZE);	// window size in ms

	channel_init();	// allow program to create named channels

	progName = argv[0];

	millis_to_timespec(&total_runtime, EXPERIMENT_RUNTIME_MS);

	// Initialize all labels
	if (label_init() != EOK) {
		printf("[Main] Error initializing labels!\r\n");
		return EXIT_FAILURE;
	}

	// Register all APS threads to the system
	REGISTER_APS_PARTITIONS

	// Register all threads to the system
	REGISTER_THREADS

	printf("\n");
	if (aps_configure_user_configuration() == -1) {
		printf("[Main] Error initializing APS partitions!\r\n");
		return EXIT_FAILURE;
	}

	thread_configureStrictPriorities();

	//initialize all parts of the system
#ifdef TRACE_EXECUTION
	if (!trace_init()) {
#endif //TRACE_EXECUTION

		thread_createThreads();		// create the user threads

#ifdef TRACE_APS_BUDGETS
		create_aps_trace_thread(APS_MODE);
#endif //TRACE_APS_BUDGETS

#ifdef TRACE_EXECUTION
		trace_start();
#endif //TRACE_EXECUTION

		aps_printInfo();
		thread_printInfo();

		thread_initRunnables();			// call initialization functions of each runnable

		thread_releaseCondition();

		/**
		 * The system will run until this call returns. This is either after the specified time is passed or
		 * after a signal has been received (not supported yet).
		 */
		sleepDuration(&total_runtime);

		thread_killThreads();			// send the termination signal to all user threads

		thread_joinThreads();			// wait for all user threads to finish

		thread_saveAllMeasurements();	// Save all measurement data to text files

		thread_deinitRunnables();		// call deinitialization functions of each runnable

#ifdef TRACE_EXECUTION
		trace_stop();
	}
#endif //TRACE_EXECUTION

	thread_printStatistics();

	return EXIT_SUCCESS;
}

