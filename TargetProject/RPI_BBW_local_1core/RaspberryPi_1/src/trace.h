/*
 * trace.h
 *
 *  Created on: 20 Jul 2021
 *      Author: mabecker
 */

#ifndef TRACE_H_
#define TRACE_H_

#include <sys/trace.h>
#include "instrex.h"

#define ID_USER_START_EVENT				100
#define ID_USER_END_EVENT				200
#define ID_USER_RELEASE_EVENT			300
#define ID_USER_APS_LOGGING_EVENT		400
#define ID_USER_REGISTER_PRECEDENCE		500
#define ID_USER_REGISTER_PERIOD			501
#define ID_USER_REGISTER_WCET			502
#define ID_USER_REGISTER_NAME 			503
#define ID_USER_APS_PARTITION_INFO		504
#define ID_USER_REGISTER_PRIORITY		505
extern char *progName;

/**
 * X -> pointer to the thread_data
 */
#define TRACE_THREAD_JOB_START(X)		TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_START_EVENT, X->thread_id, X->current_job_id));
#define TRACE_THREAD_JOB_END(X)			TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_END_EVENT, X->thread_id, X->current_job_id - 1));
#define TRACE_THREAD_RELEASE_JOBS()		TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_RELEASE_EVENT, 0, 0));
#define TRACE_APS_LOGGING_START(X)		TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_APS_LOGGING_EVENT, X->thread_id, 0));
#define TRACE_REG_PRECEDENCE(X, Y)		TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_REGISTER_PRECEDENCE, X->thread_id, Y->thread_id));
#define TRACE_REG_PERIOD(X, Y)			TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_REGISTER_PERIOD, X->thread_id, Y));
#define TRACE_REG_WCET(X)				TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_REGISTER_WCET, X->thread_id, X->exec_time_us));
#define TRACE_REG_NAME(X)				TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, ID_USER_REGISTER_NAME, X));
#define TRACE_REG_PRIORITY(X)			TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, ID_USER_REGISTER_PRIORITY, X->thread_id, X->priority));
#define TRACE_APS_PARTITION_INFO(X)		TRACE_EVENT(progName, TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, ID_USER_APS_PARTITION_INFO, X));

/**
 * Function initializes the trace settings. I.e. disable events we don't need and only record events of our process.
 * Call this function early on in main(...)
 */
int trace_init();

/**
 * Function triggers the tracelogger which starts recording of the trace.
 * Call this sometime after trace_init()
 */
void trace_start();

/**
 * Function stops trace recording.
 * Call this sometime after trace_start()
 */
void trace_stop();

#endif /* TRACE_H_ */
