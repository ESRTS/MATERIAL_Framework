/*
 * aps.c
 *
 *  Created on: 10.06.2021
 *      Author: ADD5KOR
 */
#include "aps.h"
#include "time_funcs.h"
#include "trace.h"
#include <sys/neutrino.h>

/**
 * Start of the linked list with all (user) partition information
 */
struct partition_data* partitions;

int user_partition_count = 1;

int aps_sched_flags = 0;

//buffer used to create the string that holds the readable budget (only for printing)
char print_budget_buffer[20];

sched_aps_info* aps_getInfo() {
	sched_aps_info* aps_info = malloc(sizeof(sched_aps_info));
	APS_INIT_DATA(aps_info);
	int ret = SchedCtl(SCHED_APS_QUERY_PARMS, aps_info, sizeof(sched_aps_info));
	if (EOK!=ret) {
			printf("Error in retrieving aps info  %s (%d).\n", strerror(errno), errno);
			return NULL;
	}
	return aps_info;
}

int aps_createPartition(int budget_percent, int budget_percent_scale, char* name) {

	sched_aps_create_parms partition;
	APS_INIT_DATA(&partition);
	partition.budget_percent_scale = budget_percent_scale;
	partition.budget_percent = budget_percent;
	partition.critical_budget_ms = 0;
	partition.max_budget_percent = budget_percent;
	partition.critical_budget_ms = -1;
	partition.critical_priority = -1;
	partition.name = name;
	int ret = SchedCtl( SCHED_APS_CREATE_PARTITION, &partition,	sizeof(partition));
	if (ret != EOK) {
		printf("Couldn't create partition \"%s\" budget: %i budget percent scale: %i : %s (%d).\n", partition.name, budget_percent, budget_percent_scale, strerror(errno), errno);
		return -1;
	} else {
		printf ("The new partition's ID is %d.\n", partition.id);
	}

	return partition.id;
}

/*
typedef struct {
	int16_t id;
	int16_t new_budget_percent;
	int16_t new_critical_budget_ms;
	int16_t new_max_budget_percent;
	int16_t new_critical_priority;
	uint16_t budget_percent_scale;
	int32_t reserved1;
	int64_t reserved2;
} sched_aps_modify_parms;
 */
int aps_modifyPartitionBudget(int id, int new_budget_percent, int budget_percent_scale) {
	sched_aps_modify_parms new_params;
	APS_INIT_DATA(&new_params);
	new_params.id = id;
	new_params.new_budget_percent = new_budget_percent;
	new_params.budget_percent_scale = budget_percent_scale;
	new_params.new_critical_budget_ms = -1;
	new_params.new_critical_priority = -1;
	new_params.new_max_budget_percent = new_budget_percent;

	int ret = SchedCtl( SCHED_APS_MODIFY_PARTITION, &new_params, sizeof(new_params) );
	if (EOK!=ret) {
		printf("[APS] Error in modifying partition budget of partition %d - %s (%d).\n", new_params.id, strerror(errno), errno);
		return -1;
	}
	else {
		printf( "[APS] Setting the new budget of partition %d to %s%%\n", new_params.id, aps_prettyBudget(new_params.new_budget_percent, new_params.budget_percent_scale));
		return id;
	}

}

char* aps_prettyBudget(int budget_percent, int budget_percent_scale) {

	float k = 0;
	int i = 0;

	for (i = 1; i <= budget_percent_scale; i++) {
		if (i == 1) k = 10;
		else k = k * 10;
	}

	float budget = (float)budget_percent;
	if (k != 0) budget = budget / k;
	sprintf(print_budget_buffer, "%08.4f", budget);

	return print_budget_buffer;
}

//void set_hard_reservation(int id, int budget_percentage) {
//	sched_aps_modify_parms new_params;
//	APS_INIT_DATA(&new_params);
//	new_params.id = id;
//	new_params.new_budget_percent = budget_percentage;
//	new_params.new_critical_budget_ms = -1;
//	new_params.new_critical_priority = -1;
//	new_params.budget_percent_scale = 0;
//	new_params.new_max_budget_percent = budget_percentage;
//
//	int ret = SchedCtl( SCHED_APS_MODIFY_PARTITION, &new_params, sizeof(new_params) );
//	if (EOK!=ret) {
//
//		printf("[APS] Error in modifying partition budget  %s (%d).\n", strerror(errno), errno);
//		return;
//	}
//	else {
//		printf( "[APS] Setting the new budget of partition %d to %d\%\n", new_params.id, new_params.new_budget_percent);
//		return;
//	}
//
//}

/**
 * typedef struct {
int32_t pid;
int32_t tid;
 out parms:
int16_t id;
int16_t inherited_id;
uint32_t crit_state_flags;
int32_t reserved1;
int32_t reserved2;
} sched_aps_query_thread_parms;
 *
 */
void aps_getThreadPartition(int tid, int pid)
{
	sched_aps_query_thread_parms tpart_info;
	int ret;
	APS_INIT_DATA(&tpart_info);
	tpart_info.pid = pid;
	tpart_info.tid = tid;

	ret = SchedCtl( SCHED_APS_QUERY_THREAD, &tpart_info, sizeof(tpart_info) );
	if (EOK!=ret) {
		printf("[APS] Error in getting partition info for thread  %s (%d).\n", strerror(errno), errno);
		return;
	}
	else {
		printf( "[APS] The id of partition of thread %d  is %d \n", tid, tpart_info.id);
		printf( "[APS] The inherited id of partition of thread %d  is %d \n", tid, tpart_info.inherited_id);
		return;
	}

}

void aps_joinPartition(int partition_id, int thread_id) {
	sched_aps_join_parms join_data;
	APS_INIT_DATA(&join_data);
	//memset(&join_data, 0, sizeof(join_data));
	join_data.id = partition_id;
	join_data.pid = getpid();
	join_data.tid = thread_id;
	int ret = SchedCtl( SCHED_APS_JOIN_PARTITION, &join_data, sizeof(join_data));
	if (ret != EOK) {
		printf("[APS] Couldn't join partition %d: %s (%d).\n",
				join_data.id, strerror(errno), errno);
	} else {
		printf ("[APS] Thread %d joined partition %d (return value %d) \n", thread_id, join_data.id, ret);
	}
}

/**
 * SCHED_APS_SCHEDPOL_LIMIT_CPU_USAGE
 * Enable enforcement of the max_budget_percent parameters, which limit the amount a partition can
 * overrun its normal budget when the system is underloaded. If this option isn't set, max_budget_percent
 * is ignored when you're setting parameters, and is reported as 100% (meaning no limit on freetime usage).
 */
void aps_configureNoOverrun() {
	sched_aps_parms sched_params;
	APS_INIT_DATA(&sched_params);

	uint32_t tmp = SCHED_APS_SCHEDPOL_LIMIT_CPU_USAGE;
	sched_params.windowsize_ms = -1;	//not set here
	sched_params.scheduling_policy_flagsp = &tmp;
	sched_params.bankruptcy_policyp = NULL; //not set here

	int ret = SchedCtl( SCHED_APS_SET_PARMS, &sched_params, sizeof(sched_params));

	if (ret != EOK) {
			printf("[APS] Couldn't configure scheduler  %s (%d).\n", strerror(errno), errno);
		} else {
			printf ("[APS] Configured partition scheduler to prohibit overruns.\n");
		}
}

/**
 * Function used to set the APS scheduler parameters.
 * Can be ored togetehr.
 * SCHED_APS_SCHEDPOL_FREETIME_BY_RATIO: the running partitions share the free time in proportion to the ratios of their budgets.
 * SCHED_APS_SCHEDPOL_DEFAULT: The scheduler hands out free time to the partition with the highest-priority running any time they aren't being limited by some other partition's right to its guaranteed minimum budget.
 * SCHED_APS_SCHEDPOL_PARTITION_LOCAL_PRIORITIES: Schedules purely by budget ratio. When enabled, the scheduler tries to balance budgets on as short a timescale as possible, regardless of the window size.
 * SCHED_APS_SCHEDPOL_LIMIT_CPU_USAGE: Enable enforcement of the max_budget_percent parameters, which limit the amount a partition can overrun its normal budget when the system is underloaded.
 */
void aps_configureScheduler(uint32_t sched_flags) {
	sched_aps_parms sched_params;
	APS_INIT_DATA(&sched_params);

	sched_params.windowsize_ms = -1;	//not set here
	sched_params.scheduling_policy_flagsp = &sched_flags;
	sched_params.bankruptcy_policyp = NULL; //not set here

	int ret = SchedCtl( SCHED_APS_SET_PARMS, &sched_params, sizeof(sched_params));

	if (ret != EOK) {
		printf("[APS] Couldn't configure scheduler  %s (%d).\n", strerror(errno), errno);
	} else {
		printf ("[APS] Configured partition scheduler to");
		if ((sched_flags & SCHED_APS_SCHEDPOL_FREETIME_BY_RATIO) != 0) printf(" SCHED_APS_SCHEDPOL_FREETIME_BY_RATIO");
		if (sched_flags == SCHED_APS_SCHEDPOL_DEFAULT) printf(" SCHED_APS_SCHEDPOL_DEFAULT");
		if ((sched_flags & SCHED_APS_SCHEDPOL_PARTITION_LOCAL_PRIORITIES) != 0) printf(" SCHED_APS_SCHEDPOL_PARTITION_LOCAL_PRIORITIES");
		if ((sched_flags & SCHED_APS_SCHEDPOL_LIMIT_CPU_USAGE) != 0) printf(" SCHED_APS_SCHEDPOL_LIMIT_CPU_USAGE");
		printf(".\n");
	}
}

void aps_configureWindowSize(int16_t window_size_ms) {
	sched_aps_parms sched_params;
	APS_INIT_DATA(&sched_params);

	sched_params.windowsize_ms = window_size_ms;
	sched_params.scheduling_policy_flagsp = NULL; //not set here
	sched_params.bankruptcy_policyp = NULL; //not set here
	int ret = SchedCtl( SCHED_APS_SET_PARMS, &sched_params, sizeof(sched_aps_parms));

	if (ret != EOK) {
		printf("[APS] Couldn't configure APS window size  %s (%d).\n", strerror(errno), errno);
	} else {
		printf ("[APS] Configured APS window size to %i ms.\n", window_size_ms);
	}
}

void aps_registerApsScheduler(uint32_t sched_flags) {
	aps_sched_flags = sched_flags;
}

/**
 * This function adds a new user APS partition description to the system.
 * The function does not yet configure QNX with this information!
 *
 * budget is given as integer. The last PARTITION_PERCENTAGE_SCALE_FACTOR digits are after the decimal point.
 */
struct partition_data* aps_add_partition_description(char* name, int budget, int budgetScalingFactor) {
	struct partition_data* new_partition = malloc(sizeof(struct partition_data));

	if (new_partition == NULL) {
		printf("ERROR: Could not allocate memory for new partition data (%s, %d)\n", __FILE__, __LINE__);
		return NULL;
	}
	new_partition->budget = budget;
	new_partition->name = name;
	new_partition->id = user_partition_count;
	new_partition->budget_percentage_scale = budgetScalingFactor;

	if (partitions == NULL) partitions = new_partition;
	else {
		struct partition_data* tmp = partitions;

		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new_partition;
	}

	user_partition_count++;

	return new_partition;
}

/**
 * Helper function to print a table with each user partition's description.
 */
void aps_printInfo() {
	printf("---------------------------------------\n");
	printf("| Name               | ID | Budget    |\n");
	printf("---------------------------------------\n");

	char traceBuffer[50];

	struct partition_data* list_pointer = partitions;

	if (list_pointer != NULL) {
		do {
			printf("| %18s | %2d | %s%% |\n", list_pointer->name, list_pointer->id, aps_prettyBudget(list_pointer->budget, list_pointer->budget_percentage_scale));
			printf("---------------------------------------\n");

			sprintf(traceBuffer, " %i %s %s ", list_pointer->id, list_pointer->name, aps_prettyBudget(list_pointer->budget, list_pointer->budget_percentage_scale));
			TRACE_APS_PARTITION_INFO(traceBuffer);
			list_pointer = list_pointer->next;
		} while (list_pointer != NULL);
	}
}

/**
 * This function is called after all user partitions have been registered with add_partition_description(...).
 * The function then sets all existing user partitions to a budget of 0 (as partitions can't be deleted).
 * After, the partitions for this setting are configured.
 */
int aps_configure_user_configuration() {
	int i = 0;
	sched_aps_info* aps_info = aps_getInfo();
	struct partition_data* data = partitions;
	int retval;
	int num_user_partitions;

	if (aps_info->max_partitions < user_partition_count) {
		printf("Error: Can't configure %d partitions! Max partitions is %d\n", user_partition_count, aps_info->max_partitions);
		return -1;
	}

	printf("[APS] The cycles per ms is %d \n", aps_info->cycles_per_ms);
	printf("[APS] The configured window size is %d ms \n", aps_info->windowsize_ms);
	printf("[APS] The maximum number of partitions in the system is %d \n", aps_info->max_partitions);

	//configure the APS scheduler to be used
	aps_configureScheduler(aps_sched_flags);

	num_user_partitions = aps_info->num_partitions - 1;

	// set all existing user partitions to unused (i.e. budget = 0)
	printf("[APS] Disabling all %i existing user partitions!\n", num_user_partitions);
	for (i = 0; i < num_user_partitions; i++) {
		aps_modifyPartitionBudget(i+1, 0, 1);

		//check what happens if no partition name is provided
	}

	// configure the partitions for this setting
	printf("[APS] Configure all user partitions for configuration!\n");
	while (data != NULL) {

		if (data->id <= num_user_partitions) {

			retval = aps_modifyPartitionBudget(data->id, data->budget, data->budget_percentage_scale);
			if (retval == -1) {
				printf("Error: Can't modify budget of partition %s! \n", data->name);
				return -1;
			}
		} else {

			retval = aps_createPartition(data->budget, data->budget_percentage_scale, data->name);
			if (retval == -1) {
				printf("Error: Can't create new partition (tried to create partition %s)! \n", data->name);
				return -1;
			}
		}
		data = data->next;
	}

	return 0;
}

void aps_configure_os_tick(uint32_t tick_period_ns) {
	struct _clockperiod new_period;

	new_period.fract = 0; 		//this value is reserved by QNX for future use and shall be 0
	new_period.nsec = tick_period_ns;	//500us

	//set the OS tick
	int ret = ClockPeriod(CLOCK_REALTIME, &new_period, NULL, 0);
	if (ret == -1) {
		printf("[APS] Couldn't set new OS tick  %s (%d).\n", strerror(errno), errno);
	} else {
		printf("[APS] Set OS tick period to %i [ns]\n", tick_period_ns);
	}
}
