/*
 * channel.h
 *
 *  Created on: 25 Jan 2024
 *      Author: mabecker
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <sys/neutrino.h>
#include <inttypes.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <unistd.h>
#include <sys/dispatch.h>
#include <sys/procmgr.h>
 #include <sys/syspage.h>

/**
 * Type used to identify all messages sent by a user communication channel.
 */
#define CHANNEL_MSG_TYPE 10

/**
 * Status used to send back to the client to indicate that the message was received ok.
 */
#define REPLY_OK 20

/* We specify the header as being at least a pulse */
typedef struct _pulse msg_header_t;


/**
 * Struct type to encapsulate the information needed for one communication channel.
 */
typedef struct {
	char* name;				// Global name of the channel

	int	server_coid;		// ID to identify the channel a client uses to connect to the server [CLIENT ONLY]

	name_attach_t* server;	// Attach struct used by servers to store information on the created channel [SERVER ONLY]

	void* msg;				// Pointer to the memory area used to prepare/store a message

	bool ready;				// A flag to indicate that the channel is configured and can be used
} channel_t;

/**
 * Struct we use to send at the beginning of each message
 */
typedef struct {
	msg_header_t hdr;		// Message header used by QNX

	uint8_t type;			// Type of this message
} msg_common_t;

void channel_init();
bool channel_create(channel_t* channel);
bool channel_connect(channel_t* channel);
void channel_cleanup(channel_t* channel);
bool channel_send(channel_t* channel, uint8_t* data, int size);
bool channel_receive(channel_t* channel, uint8_t* data, int size);
#endif /* CHANNEL_H_ */
