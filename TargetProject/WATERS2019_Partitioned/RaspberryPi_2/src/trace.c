/*
 * trace.c
 *
 *  Created on: 20 Jul 2021
 *      Author: mabecker
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "trace.h"
#include <process.h>
#include <sys/trace.h>
#include "instrex.h"
#include "sysConfig.h"

/* Used for the TRACE_EVENT and defined in main.c  */
extern char* progName;

/* Uncomment to trace all events instead of the selected ones only */
//#define TRACE_ALL_EVENTS

/* Used to create the command string that is sent to system() */
#define CMD_BUFFER_SIZE	70
char cmd_buffer[CMD_BUFFER_SIZE];

/**
 * Prepare everything for the traceing. This means that all event that we
 * require are specified.
 */
int trace_init(){

	int rc;
	pid_t pid = getpid();

	/**
	 * Tracelogger is started in deamon mode.
	 * This way it does not directly start recording and it waits until the application sends
	 * the event _NTO_TRACE_START to start it and _NTO_TRACE_STOP to stop it.
	 * The functions trace_start() and trace_stop() send those events.
	 */
	strncat(cmd_buffer, "tracelogger -d1 -r -f /dev/shmem/trace_", CMD_BUFFER_SIZE);
	strncat(cmd_buffer, SETTING_NAME, CMD_BUFFER_SIZE);
	strncat(cmd_buffer, ".kev &", CMD_BUFFER_SIZE);

	rc = system(cmd_buffer);
	if (rc == -1) {
		printf("tracelogger could not be started!");
		return EXIT_FAILURE;
	}
	sleep(1);

	/*
	 * Just in case, turn off all filters, since we
	 * don't know their present state - go to the
	 * known state of the filters.
	 */
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_DELALLCLASSES));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_KERCALL));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_KERCALL));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_THREAD));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_THREAD));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_VTHREAD));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_VTHREAD));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_SYSTEM));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_SYSTEM));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_COMM));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_COMM));

	 /*
	  * Set wide emitting mode for all classes and
	  * their events.
	  * Needed for APS events.
	  */
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_SETALLCLASSESWIDE));

	 /*
	  * Intercept all event classes
	  */
#ifdef TRACE_ALL_EVENTS
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDALLCLASSES));
#else
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_THREAD));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_PROCESS, _NTO_TRACE_PROCCREATE_NAME));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM, _NTO_TRACE_SYS_APS_NAME));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_BUDGETS));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_PSTATS));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_OSTATS));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_INFO));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_JOIN));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_THREAD));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_PROCESS));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_APS_BNKR));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_SCHED_CONF));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_POWER));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_SYSTEM,_NTO_TRACE_SYS_TIMER));


	// TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_DELCLASS, _NTO_TRACE_KERCALL));

	 /**
	  * Required to handle buffer and timestamps
	  */
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_CONTROL));

	 /**
	  * Intercept all user events
	  */
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_USER));

#endif

	 /**
	  * Limit to the events of this process only
	  */
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_SETCLASSPID, _NTO_TRACE_THREAD, pid));
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_SETCLASSPID, _NTO_TRACE_SYSTEM, pid));


	 return EXIT_SUCCESS;
}

/**
 * Start the traceing.
 * At this point the tracelogger must be running in deamon mode.
 * tracelogger -d1 -n 3 -f /dev/shmem/ruleValidation.kev
 */
void trace_start(){
	 /*
	  * Start tracing process
	  *
	  * During the tracing process, the tracelogger (which
	  * is being executed in a daemon mode) will log all events.
	  * You can specify the number of iterations (i.e., the
	  * number of kernel buffers logged) when you start tracelogger.
	  */
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_START));

}

void trace_stop(){
	 /*
	  * Start tracing process
	  *
	  * During the tracing process, the tracelogger (which
	  * is being executed in a daemon mode) will log all events.
	  * You can specify the number of iterations (i.e., the
	  * number of kernel buffers logged) when you start tracelogger.
	  */
	 TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_STOP));

}
