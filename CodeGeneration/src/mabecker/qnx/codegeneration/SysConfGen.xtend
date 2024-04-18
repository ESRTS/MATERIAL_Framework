package mabecker.qnx.codegeneration

import mabecker.qnx.codegeneration.model.QnxNode

class SysConfGen {
	
	static def generateHeader(String settingName, int runtime_ms, boolean recordExecTrace, boolean recordApsTrace, QnxNode node) {//ArrayList<Task> tasks, mabecker.qnx.codegeneration.AmaltheaWrapper wrapper, HwStructure ecu) {
		'''
			/*
			 * sysConfig.h
			 */
			
			#ifndef SYSCONFIG_H_
			#define SYSCONFIG_H_
			#include "thread.h"
			
			/**
			 * Bitmasks used to assign core affinities
			 */
			«FOR c : node.cores»
				#define CORE«c.id»	«Generator.generateCoreBitmap(c)»
			«ENDFOR»
			
			/**
			 * Definitions for APS partition IDs
			 */
			«FOR p : node.partitions»
				#define «p.name.replace(' ', '_').toUpperCase»	«node.partitions.indexOf(p)»
			«ENDFOR»
			
			#define APS_WINDOW_SIZE	«node.apsWindowsizeMs»
			
			/**
			 * IP address of this node
			 */
			#define LOCAL_IP_ADDRESS 	"«node.ipAddress»"
			
			/**
			 * Name of the configuration. This is used as filename for the trace file.
			 */
			#define SETTING_NAME "«settingName»"
			
			/**
			 * Enable the APS budget tracing
			 */
			«IF recordApsTrace == true»
				#define TRACE_APS_BUDGETS
			«ELSE»
				//#define TRACE_APS_BUDGETS
			«ENDIF»
			/**
			 * Enable to collect the execution trace using tracelogger
			 */
			«IF recordExecTrace == true»
				#define TRACE_EXECUTION
			«ELSE»
				//#define TRACE_EXECUTION
			«ENDIF»
			
			/**
			 * Duration of the experiment in ms
			 */
			#define EXPERIMENT_RUNTIME_MS «runtime_ms»
			
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
			«FOR p : node.partitions»
				«IF p.isSystemPartition == false»
					aps_add_partition_description("«p.name»", «p.budgetPercent», «p.budgetPercentageScale»);\
				«ENDIF»
			«ENDFOR»
			
			#define REGISTER_THREADS  \
			«FOR t : node.allTasks»
				thread_addThreadDescription("«t.name»", «t.period_ms», «t.deadline_ms», 0, «t.priority», «Generator.generateCoreAffinityString(t)», «t.partition.name.replace(' ', '_').toUpperCase»);\
			«ENDFOR»
				/* Register runnables for all tasks */\
			«FOR t : node.allTasks»
				«FOR r : t.runnables»
					thread_registerRunnable("«t.name»", &«r.name»);\
				«ENDFOR»
			«ENDFOR»
				
			#endif /* SYSCONFIG_H_ */
			
		'''
	}
}
