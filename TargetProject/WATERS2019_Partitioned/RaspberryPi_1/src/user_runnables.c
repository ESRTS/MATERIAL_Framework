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
 * Generated initialization function for runnable CAN_Func
 */
__attribute__((weak)) void r_CAN_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable CAN_Func
 */
__attribute__((weak)) void r_CAN_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(516, spec->cid); // Execute for 516 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable CAN_Func
 */
__attribute__((weak)) void r_CAN_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable EKF_Func
 */
__attribute__((weak)) void r_EKF_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable EKF_Func
 */
__attribute__((weak)) void r_EKF_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(4099, spec->cid); // Execute for 4099 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable EKF_Func
 */
__attribute__((weak)) void r_EKF_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Tx_EKF_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_EKF_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
		
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(EKF_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct
	
		channel->name = "EKF_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
	
		channel_connect(channel);
	
		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Tx_EKF_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_EKF_to_RaspberryPi_2(runnable_spec_t* spec) {

	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data

	EKF_to_RaspberryPi_2_t* msg = channel->msg;
	msg->common.hdr.type = CHANNEL_MSG_TYPE;

	uint8_t* writePointer = msg->payload;

	/* Fill the payload section of the message with all label data */
	for (int i = 0; i < spec->inputLabelCount; i++) {
		memcpy(writePointer, spec->inputData[i]->data, spec->inputData[i]->size);	// Copy the label to the msg payload
		writePointer += spec->inputData[i]->size;									// Move the write pointer after the label we just wrote
	}

	channel_send(channel, (uint8_t*)msg, sizeof(EKF_to_RaspberryPi_2_t));	// Send the message to the server
}

/**
 * Generated deinitialization function for runnable Tx_EKF_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_EKF_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Lidar_Func
 */
__attribute__((weak)) void r_Lidar_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable Lidar_Func
 */
__attribute__((weak)) void r_Lidar_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(11763, spec->cid); // Execute for 11763 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable Lidar_Func
 */
__attribute__((weak)) void r_Lidar_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Tx_Lidar_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Lidar_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
		
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(Lidar_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct
	
		channel->name = "Lidar_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
	
		channel_connect(channel);
	
		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Tx_Lidar_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Lidar_to_RaspberryPi_2(runnable_spec_t* spec) {

	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data

	Lidar_to_RaspberryPi_2_t* msg = channel->msg;
	msg->common.hdr.type = CHANNEL_MSG_TYPE;

	uint8_t* writePointer = msg->payload;

	/* Fill the payload section of the message with all label data */
	for (int i = 0; i < spec->inputLabelCount; i++) {
		memcpy(writePointer, spec->inputData[i]->data, spec->inputData[i]->size);	// Copy the label to the msg payload
		writePointer += spec->inputData[i]->size;									// Move the write pointer after the label we just wrote
	}

	channel_send(channel, (uint8_t*)msg, sizeof(Lidar_to_RaspberryPi_2_t));	// Send the message to the server
}

/**
 * Generated deinitialization function for runnable Tx_Lidar_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Lidar_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Detection_Func
 */
__attribute__((weak)) void r_Detection_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable Detection_Func
 */
__attribute__((weak)) void r_Detection_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(78972, spec->cid); // Execute for 78972 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable Detection_Func
 */
__attribute__((weak)) void r_Detection_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Tx_Detection_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Detection_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
		
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(Detection_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct
	
		channel->name = "Detection_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
	
		channel_connect(channel);
	
		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Tx_Detection_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Detection_to_RaspberryPi_2(runnable_spec_t* spec) {

	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data

	Detection_to_RaspberryPi_2_t* msg = channel->msg;
	msg->common.hdr.type = CHANNEL_MSG_TYPE;

	uint8_t* writePointer = msg->payload;

	/* Fill the payload section of the message with all label data */
	for (int i = 0; i < spec->inputLabelCount; i++) {
		memcpy(writePointer, spec->inputData[i]->data, spec->inputData[i]->size);	// Copy the label to the msg payload
		writePointer += spec->inputData[i]->size;									// Move the write pointer after the label we just wrote
	}

	channel_send(channel, (uint8_t*)msg, sizeof(Detection_to_RaspberryPi_2_t));	// Send the message to the server
}

/**
 * Generated deinitialization function for runnable Tx_Detection_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Detection_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Localization_Func
 */
__attribute__((weak)) void r_Localization_Func_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable Localization_Func
 */
__attribute__((weak)) void r_Localization_Func(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(348801, spec->cid); // Execute for 348801 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable Localization_Func
 */
__attribute__((weak)) void r_Localization_Func_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Tx_Localization_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Localization_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
		
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(Localization_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct
	
		channel->name = "Localization_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
	
		channel_connect(channel);
	
		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Tx_Localization_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Localization_to_RaspberryPi_2(runnable_spec_t* spec) {

	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data

	Localization_to_RaspberryPi_2_t* msg = channel->msg;
	msg->common.hdr.type = CHANNEL_MSG_TYPE;

	uint8_t* writePointer = msg->payload;

	/* Fill the payload section of the message with all label data */
	for (int i = 0; i < spec->inputLabelCount; i++) {
		memcpy(writePointer, spec->inputData[i]->data, spec->inputData[i]->size);	// Copy the label to the msg payload
		writePointer += spec->inputData[i]->size;									// Move the write pointer after the label we just wrote
	}

	channel_send(channel, (uint8_t*)msg, sizeof(Localization_to_RaspberryPi_2_t));	// Send the message to the server
}

/**
 * Generated deinitialization function for runnable Tx_Localization_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_Localization_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

