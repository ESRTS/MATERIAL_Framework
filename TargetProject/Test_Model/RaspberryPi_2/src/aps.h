/*
 * aps.h
 *
 *  Created on: 10.06.2021
 *      Author: ADD5KOR
 */
#ifndef APS_H_
#define APS_H_

#include <sys/sched_aps.h>	// sched_aps_create_parms
#include "time_funcs.h"

/**
 * Data structure to describe an APS partition
 */
struct partition_data {

	//partition id is assigned by QNX
	int id;

	//budget of the partition
	int budget;

	//number of digits right to the decimal point
	int budget_percentage_scale;

	//name of the partition
	char* name;
	struct partition_data* next;
};

sched_aps_info* aps_getInfo();
void aps_joinPartition(int partition_id, int thread_id);
int aps_createPartition(int budget_percent, int budget_percent_scale, char* name);
int aps_modifyPartition_Budget(int id, int new_budget_percent, int budget_percent_scale);
//void set_hard_reservation(int id, int budget_percentage);
void aps_getThreadPartition(int tid, int pid);
void aps_configureNoOverrun();
void configure_aps_scheduler(uint32_t sched_flags);
void aps_printInfo();
struct partition_data* aps_add_partition_description(char* name, int budget, int budgetScalingFactor);
void aps_registeApsScheduler(uint32_t sched_flags);
int aps_configure_user_configuration();
char* aps_prettyBudget(int budget_percent, int budget_percent_scale);
void aps_configure_os_tick(uint32_t tick_period_ns);
void aps_configureWindowSize(int16_t window_size_ms);
#endif /* APS_H_ */
