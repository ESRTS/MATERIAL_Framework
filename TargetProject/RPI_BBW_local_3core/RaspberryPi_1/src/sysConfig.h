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
#define N1_P0	1

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
aps_add_partition_description("N1_P0", 250, 1);\

#define REGISTER_THREADS  \
thread_addThreadDescription("pBrakePedalLDM", 20, 10, 0, 250, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("pBrakeTorqueMap", 30, 10, 0, 249, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("pGlobalBrakeController", 40, 10, 0, 248, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("ABS_FL_Pt", 50, 10, 0, 247, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("pLDM_Brake_FL", 60, 10, 0, 243, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("ABS_FR_Pt", 50, 10, 0, 246, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("pLDM_Brake_FR", 60, 10, 0, 242, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("ABS_RL_Pt", 50, 10, 0, 245, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("pLDM_Brake_RL", 60, 10, 0, 241, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("ABS_RR_Pt", 50, 10, 0, 244, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
thread_addThreadDescription("pLDM_Brake_RR", 60, 10, 0, 240, CORE0|CORE1|CORE2, SYSTEM_PARTITION);\
	/* Register runnables for all tasks */\
thread_registerRunnable("pBrakePedalLDM", &BrakePedalLDM_T);\
thread_registerRunnable("pBrakeTorqueMap", &BrakeTorqMap);\
thread_registerRunnable("pGlobalBrakeController", &GlobalBrakeController);\
thread_registerRunnable("ABS_FL_Pt", &ABS_FL_T);\
thread_registerRunnable("pLDM_Brake_FL", &BrakeActuator_FL_LDM);\
thread_registerRunnable("ABS_FR_Pt", &ABS_FR_T);\
thread_registerRunnable("pLDM_Brake_FR", &BrakeActuator_FR_LDM);\
thread_registerRunnable("ABS_RL_Pt", &ABS_RL_T);\
thread_registerRunnable("pLDM_Brake_RL", &BrakeActuator_RL_LDM);\
thread_registerRunnable("ABS_RR_Pt", &ABS_RR_T);\
thread_registerRunnable("pLDM_Brake_RR", &BrakeActuator_RR_LDM);\
	
#endif /* SYSCONFIG_H_ */

