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
#define LOCAL_IP_ADDRESS 	"192.168.1.211"

/**
 * Name of the configuration. This is used as filename for the trace file.
 */
#define SETTING_NAME "RaspberryPi_1"

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
thread_addThreadDescription("CAN", 10, 10, 0, 254, CORE0|CORE1|CORE2|CORE3, SYSTEM_PARTITION);\
thread_addThreadDescription("EKF", 15, 15, 0, 252, CORE3|CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("Lidar", 33, 33, 0, 251, CORE0|CORE1|CORE2|CORE3, SYSTEM_PARTITION);\
thread_addThreadDescription("Detection", 200, 200, 0, 248, CORE2|CORE0|CORE1|CORE3, SYSTEM_PARTITION);\
thread_addThreadDescription("Localization", 400, 400, 0, 247, CORE1|CORE0|CORE2|CORE3, SYSTEM_PARTITION);\
	/* Register runnables for all tasks */\
thread_registerRunnable("CAN", &CAN_Func);\
thread_registerRunnable("EKF", &EKF_Func);\
thread_registerRunnable("EKF", &Tx_EKF_to_RaspberryPi_2);\
thread_registerRunnable("Lidar", &Lidar_Func);\
thread_registerRunnable("Lidar", &Tx_Lidar_to_RaspberryPi_2);\
thread_registerRunnable("Detection", &Detection_Func);\
thread_registerRunnable("Detection", &Tx_Detection_to_RaspberryPi_2);\
thread_registerRunnable("Localization", &Localization_Func);\
thread_registerRunnable("Localization", &Tx_Localization_to_RaspberryPi_2);\
	
#endif /* SYSCONFIG_H_ */

