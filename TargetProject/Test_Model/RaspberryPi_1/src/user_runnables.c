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
 * Generated initialization function for runnable A
 */
__attribute__((weak)) void r_A_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
	
	spec->initialized = true;
}

/**
 * Generated implementation for runnable A
 */
__attribute__((weak)) void r_A(runnable_spec_t* spec) {
	
	/**
	 * Simulate the execution
	 */
	switch (spec->mode) {
		case 0:
			burn_cycles(1875, spec->cid); // Execute for 1875 us
			break;
		default:
			return;
	}
}

/**
 * Generated deinitialization function for runnable A
 */
__attribute__((weak)) void r_A_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	spec->initialized = false;
}

/**
 * Generated initialization function for runnable Tx_A_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_A_to_RaspberryPi_2_init(runnable_spec_t* spec) {
	printf("[Runnable] Initializing %s\r\n", spec->name);
		
	channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
	
	channel->msg = (void*)malloc(sizeof(A_to_RaspberryPi_2_t));	// Allocate the memory to temporarily store a message
	
	if (channel != NULL) {
		spec->user_data = channel;	// Link the channel struct to the runnable struct
	
		channel->name = "A_to_RaspberryPi_2_channel";
		channel->server_coid = -1;
		channel->server = NULL;
	
		channel_connect(channel);
	
		spec->initialized = true;
	}
}

/**
 * Generated implementation for runnable Tx_A_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_A_to_RaspberryPi_2(runnable_spec_t* spec) {

	channel_t* channel = (channel_t*)spec->user_data;	// get the channel data

	A_to_RaspberryPi_2_t* msg = channel->msg;
	msg->common.hdr.type = CHANNEL_MSG_TYPE;

	uint8_t* writePointer = msg->payload;

	/* Fill the payload section of the message with all label data */
	for (int i = 0; i < spec->inputLabelCount; i++) {
		memcpy(writePointer, spec->inputData[i]->data, spec->inputData[i]->size);	// Copy the label to the msg payload
		writePointer += spec->inputData[i]->size;									// Move the write pointer after the label we just wrote
	}

	channel_send(channel, (uint8_t*)msg, sizeof(A_to_RaspberryPi_2_t));	// Send the message to the server
}

/**
 * Generated deinitialization function for runnable Tx_A_to_RaspberryPi_2
 * This is a communication runnable (sender) and should not be changed!
 */
void r_Tx_A_to_RaspberryPi_2_deinit(runnable_spec_t* spec) {
	printf("[Runnable] Deinitializing %s\r\n", spec->name);
	
	channel_cleanup((channel_t*)spec->user_data);
	
	spec->initialized = false;
}

