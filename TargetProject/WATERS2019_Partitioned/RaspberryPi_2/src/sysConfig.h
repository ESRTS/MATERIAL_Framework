/*
 * sysConfig.h
 */

#ifndef SYSCONFIG_H_
#define SYSCONFIG_H_
#include "thread.h"

/**
 * Bitmasks used to assign core affinities
 */
#define CORE0	1
#define CORE1	2
#define CORE2	4
#define CORE3	8

/**
 * Definitions for APS partition IDs
 */
#define SYSTEM_PARTITION	0

#define APS_WINDOW_SIZE	100

/**
 * IP address of this node
 */
#define LOCAL_IP_ADDRESS 	"192.168.1.212"

/**
 * Name of the configuration. This is used as filename for the trace file.
 */
#define SETTING_NAME "RaspberryPi_2"

/**
 * Enable the APS budget tracing
 */
//#define TRACE_APS_BUDGETS
/**
 * Enable to collect the execution trace using tracelogger
 */
//#define TRACE_EXECUTION

/**
 * Duration of the experiment in ms
 */
#define EXPERIMENT_RUNTIME_MS 30000

/**
 * Select which mode is used for APS logging.
 * The APS thread is assigned to CORE1 and executes with priority 255.
 * APS_THREAD_PERIODIC
 * In periodic mode the APS thread executes periodically with a period of 1ms.
 * APS_THREAD_SPINNING
 * In spinning mode the APS thread does not sleep between consecutive jobs but keeps spinning instead.
 * This is useful if APS statistics need to be logged but at the same time all cores should be 100% utilized.
 */
#define APS_MODE APS_THREAD_SPINNING

#define REGISTER_APS_PARTITIONS \

#define REGISTER_THREADS  \
thread_addThreadDescription("Control", 5, 5, 0, 255, CORE1, SYSTEM_PARTITION);\
thread_addThreadDescription("Lane_Detection", 66, 66, 0, 249, CORE0, SYSTEM_PARTITION);\
thread_addThreadDescription("SFM", 33, 33, 0, 250, CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("Planner", 15, 15, 0, 253, CORE3, SYSTEM_PARTITION);\
thread_addThreadDescription("Listener_Lidar", -1, -1, 0, 251, CORE0, SYSTEM_PARTITION);\
thread_addThreadDescription("Listener_EKF", -1, -1, 0, 252, CORE0, SYSTEM_PARTITION);\
thread_addThreadDescription("Listener_Detection", -1, -1, 0, 248, CORE0, SYSTEM_PARTITION);\
thread_addThreadDescription("Listener_Localization", -1, -1, 0, 247, CORE0, SYSTEM_PARTITION);\
	/* Register runnables for all tasks */\
thread_registerRunnable("Control", &Control_Func);\
thread_registerRunnable("Lane_Detection", &Lane_Detection_Func);\
thread_registerRunnable("SFM", &SFM_Func);\
thread_registerRunnable("Planner", &Planner_Func);\
thread_registerRunnable("Listener_Lidar", &Rx_Lidar_to_RaspberryPi_2);\
thread_registerRunnable("Listener_EKF", &Rx_EKF_to_RaspberryPi_2);\
thread_registerRunnable("Listener_Detection", &Rx_Detection_to_RaspberryPi_2);\
thread_registerRunnable("Listener_Localization", &Rx_Localization_to_RaspberryPi_2);\
	
#endif /* SYSCONFIG_H_ */

