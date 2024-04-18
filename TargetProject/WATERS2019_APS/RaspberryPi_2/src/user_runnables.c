/*
 * user_runnables.c
 *
 * THIS FILE IS GENERATED! 
 * DON'T MODIFY BY HAND!
 */
#include <inttypes.h>
#include <stdbool.h>
#include "time_funcs.h"
#include "labels.h"
#include "labels_conf.h"
#include "channel.h"
#include "channel_conf.h"
	 
/**
 * Generated initialization function for runnable Rx_Lidar_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Lidar_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
								
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(Lidar_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct

		channel->name = "Lidar_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
		
		channel_create(channel);

		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Rx_Lidar_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Lidar_to_RaspberryPi_2(runnable_spec_t* spec) {
	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data
	
	Lidar_to_RaspberryPi_2_t* msg = channel->msg;
	
	if (channel_receive(channel, (uint8_t*)msg, sizeof(Lidar_to_RaspberryPi_2_t)) == true) {							// Receive data on the channel
	
		uint8_t* readPointer = (uint8_t*)msg->payload;											// Get a pointer to the payload
	
		for (int i = 0; i < spec->outputLabelCount; i++) {
			memcpy(spec->outputData[i]->data, readPointer, spec->outputData[i]->size);	// Copy the received label to the right position
			readPointer += spec->outputData[i]->size;									// Move the read pointer after the label we just wrote
		}
	} else {
		printf("[Runnable] Error while receiving data. Runnable:  %s\r\n", spec->name);
	}
}

/**
 * Generated deinitialization function for runnable Rx_Lidar_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Lidar_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Rx_EKF_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_EKF_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
								
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(EKF_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct

		channel->name = "EKF_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
		
		channel_create(channel);

		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Rx_EKF_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_EKF_to_RaspberryPi_2(runnable_spec_t* spec) {
	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data
	
	EKF_to_RaspberryPi_2_t* msg = channel->msg;
	
	if (channel_receive(channel, (uint8_t*)msg, sizeof(EKF_to_RaspberryPi_2_t)) == true) {							// Receive data on the channel
	
		uint8_t* readPointer = (uint8_t*)msg->payload;											// Get a pointer to the payload
	
		for (int i = 0; i < spec->outputLabelCount; i++) {
			memcpy(spec->outputData[i]->data, readPointer, spec->outputData[i]->size);	// Copy the received label to the right position
			readPointer += spec->outputData[i]->size;									// Move the read pointer after the label we just wrote
		}
	} else {
		printf("[Runnable] Error while receiving data. Runnable:  %s\r\n", spec->name);
	}
}

/**
 * Generated deinitialization function for runnable Rx_EKF_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_EKF_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Rx_Detection_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Detection_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
								
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(Detection_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct

		channel->name = "Detection_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
		
		channel_create(channel);

		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Rx_Detection_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Detection_to_RaspberryPi_2(runnable_spec_t* spec) {
	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data
	
	Detection_to_RaspberryPi_2_t* msg = channel->msg;
	
	if (channel_receive(channel, (uint8_t*)msg, sizeof(Detection_to_RaspberryPi_2_t)) == true) {							// Receive data on the channel
	
		uint8_t* readPointer = (uint8_t*)msg->payload;											// Get a pointer to the payload
	
		for (int i = 0; i < spec->outputLabelCount; i++) {
			memcpy(spec->outputData[i]->data, readPointer, spec->outputData[i]->size);	// Copy the received label to the right position
			readPointer += spec->outputData[i]->size;									// Move the read pointer after the label we just wrote
		}
	} else {
		printf("[Runnable] Error while receiving data. Runnable:  %s\r\n", spec->name);
	}
}

/**
 * Generated deinitialization function for runnable Rx_Detection_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Detection_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Rx_Localization_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Localization_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
								
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(Localization_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct

		channel->name = "Localization_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
		
		channel_create(channel);

		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Rx_Localization_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Localization_to_RaspberryPi_2(runnable_spec_t* spec) {
	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data
	
	Localization_to_RaspberryPi_2_t* msg = channel->msg;
	
	if (channel_receive(channel, (uint8_t*)msg, sizeof(Localization_to_RaspberryPi_2_t)) == true) {							// Receive data on the channel
	
		uint8_t* readPointer = (uint8_t*)msg->payload;											// Get a pointer to the payload
	
		for (int i = 0; i < spec->outputLabelCount; i++) {
			memcpy(spec->outputData[i]->data, readPointer, spec->outputData[i]->size);	// Copy the received label to the right position
			readPointer += spec->outputData[i]->size;									// Move the read pointer after the label we just wrote
		}
	} else {
		printf("[Runnable] Error while receiving data. Runnable:  %s\r\n", spec->name);
	}
}

/**
 * Generated deinitialization function for runnable Rx_Localization_to_RaspberryPi_2
 * This is a communication runnable (receiver) and should not be changed!
 */
void r_Rx_Localization_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Control_Func
 */
__attribute__((weak)) void r_Control_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable Control_Func
 */
__attribute__((weak)) void r_Control_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(1602, spec->cid); // Execute for 1602 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable Control_Func
 */
__attribute__((weak)) void r_Control_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Lane_Detection_Func
 */
__attribute__((weak)) void r_Lane_Detection_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable Lane_Detection_Func
 */
__attribute__((weak)) void r_Lane_Detection_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(51044, spec->cid); // Execute for 51044 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable Lane_Detection_Func
 */
__attribute__((weak)) void r_Lane_Detection_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable SFM_Func
 */
__attribute__((weak)) void r_SFM_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable SFM_Func
 */
__attribute__((weak)) void r_SFM_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(32209, spec->cid); // Execute for 32209 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable SFM_Func
 */
__attribute__((weak)) void r_SFM_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Planner_Func
 */
__attribute__((weak)) void r_Planner_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable Planner_Func
 */
__attribute__((weak)) void r_Planner_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(11403, spec->cid); // Execute for 11403 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable Planner_Func
 */
__attribute__((weak)) void r_Planner_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

