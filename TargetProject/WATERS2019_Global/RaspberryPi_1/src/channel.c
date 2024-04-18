/*
 * channel.c
 *
 *  Created on: 25 Jan 2024
 *      Author: mabecker
 */
#include "stdbool.h"
#include <sys/procmgr.h>
#include "channel.h"

/**
 * Message information for the receiver.
 */
struct _msg_info info;

/**
 * Function sets the ability to the program to create named channels
 */
void channel_init() {
	/* Enable PROCMGR_AID_PUBLIC_CHANNEL in order to be able to create
	 * a public channel */
	int retval = procmgr_ability(0,
			PROCMGR_ADN_ROOT|PROCMGR_AOP_ALLOW|PROCMGR_AID_PUBLIC_CHANNEL,
			PROCMGR_ADN_NONROOT|PROCMGR_AOP_ALLOW|PROCMGR_AID_PUBLIC_CHANNEL,
			PROCMGR_AID_EOL);
	if (retval == EOK) {
		printf("Enabled the ability PROCMGR_AID_PUBLIC_CHANNEL\r\n");
	} else {
		printf("ERROR: During call to procmgr_ability! (%s, %d)\r\n", __FILE__, __LINE__);
		printf("ERRNO: %d (%s)\n", errno, strerror(errno));
	}
}

/**
 * Function to create a new global named channel for a server thread
 */
bool channel_create(channel_t* channel) {

	channel->ready = false;

	/**
	 * Create the communication channel
	 */
	int tmpCid = ChannelCreate(0);
	if (tmpCid == -1) {
		printf("ERROR: During call to ChannelCreate for channel %s! (%s, %d)\r\n", channel->name,  __FILE__, __LINE__);
		printf("ERRNO: %d (%s)\n", errno, strerror(errno));

		return false;
	} else {
		printf("[Channel] Created channel %s with ID-%i\n", channel->name, tmpCid);
	}

	/**
	 * Allocate a dispatch structure with the channel ID of teh channel we created
	 */
	dispatch_t* dpp = dispatch_create_channel(tmpCid, 0);

	/**
	 * Attach a global name to the channel
	 */
	if ((channel->server = name_attach(dpp, channel->name, NAME_FLAG_ATTACH_GLOBAL)) == NULL) {
		printf("ERROR: During call to ChannelCreate channel %s! (%s, %d)\r\n", channel->name, __FILE__, __LINE__);
		printf("ERRNO: %d (%s)\n", errno, strerror(errno));

		return false;
	} else {
		printf("[Channel] Created named channel /dev/name/global/%s with ID-%i\n", channel->name, channel->server->chid);
	}

	channel->ready = true;
	return true;
}

/**
 * Function to connect to a global named channel for a client thread
 */
bool channel_connect(channel_t* channel) {

	channel->ready = false;

	if ((channel->server_coid = name_open(channel->name, NAME_FLAG_ATTACH_GLOBAL | _NTO_CHF_FIXED_PRIORITY)) == -1) {
		printf("ERROR: During call to name_open! ( %s, %d)\r\n", __FILE__, __LINE__);
		printf("ERRNO: %d (%s)\n", errno, strerror(errno));
		return false;
	} else {
		printf("[Channel] Successfully opened the channel %s!\r\n", channel->name);
	}

	channel->ready = true;
	return true;
}

/**
 * Function to send payload over an existing channel (client)
 */
bool channel_send(channel_t* channel, uint8_t* data, int size) {

	if (channel->ready == true) {	// Only send a message on a ready channel!
		msg_header_t replyMsg;	// space for the reply message. The pulse header is sufficient as no data is sent back.

		msg_common_t* common = (msg_common_t*) data;
		common->type = CHANNEL_MSG_TYPE;

		long replyStatus = MsgSend(channel->server_coid, data, size, &replyMsg, sizeof(replyMsg));
		if (replyStatus == -1) {
			printf("ERROR: During call to MsgSend! (Channel %s, %s, %d) --> Marking channel as not ready!\r\n", channel->name, __FILE__, __LINE__);
			printf("ERRNO: %d (%s)\n", errno, strerror(errno));
			channel->ready = false;
		} else {
			if (replyStatus != REPLY_OK) {
				printf("ERROR: Received unexpected reply status &i (Channel %s, %s, %d)\r\n", replyStatus, channel->name, __FILE__, __LINE__);	// For now we don't mark the channel as not ready here
			}
		}
	}
	return true;
}

/**
 * Function to receive data on an existing channel (server)
 */
bool channel_receive(channel_t* channel, uint8_t* data, int size) {

	if (channel->ready == true) {	// Only send a message on a ready channel!
		int rcvid;

		msg_header_t replyMsg;

		rcvid = MsgReceive(channel->server->chid, data, size, &info);

		if (rcvid == -1) {
			printf("ERROR: During call to MsgReceive on channel %s! (%s, %d)\r\n", channel->name, __FILE__, __LINE__);
			printf("ERRNO: %d (%s)\n", errno, strerror(errno));
			channel->ready = false;
			return false;
		}

		msg_common_t* common = (msg_common_t*) data;

		if (rcvid == 0) {/* Pulse received */
			switch (common->hdr.code) {
			case _PULSE_CODE_DISCONNECT:
				/*
				 * A client disconnected all its connections (called
				 * name_close() for each name_open() of our name) or
				 * terminated
				 */
				printf("[Channel] Received pulse: _PULSE_CODE_DISCONNECT\r\n");
				ConnectDetach(common->hdr.scoid);
				break;
			case _PULSE_CODE_UNBLOCK:
				/*
				 * REPLY blocked client wants to unblock (was hit by
				 * a signal or timed out).  It's up to you if you
				 * reply now or later.
				 */
				printf("[Channel] Received pulse: _PULSE_CODE_UNBLOCK\r\n");
				break;
			default:
				/*
				 * A pulse sent by one of your processes or a
				 * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
				 * from the kernel?
				 */
				printf("[Channel] Received pulse: default\r\n");
				break;
			}
		}

		/* If the Global Name Service (gns) is running, name_open()
		   sends a connect message. The server  must EOK it. */
		if (common->hdr.type == _IO_CONNECT ) {
			MsgReply( rcvid, EOK, NULL, 0 );
		}

		/* Some other I/O message was received; reject it */
		if (common->hdr.type > _IO_BASE && common->hdr.type <= _IO_MAX ) {
			printf("[Channel] Received some I/O message\r\n");
			MsgError( rcvid, ENOSYS );
		}

		switch (common->type){
		case CHANNEL_MSG_TYPE:

			// Send the reply to the client thread
			if (MsgReply(rcvid, REPLY_OK, &replyMsg, sizeof(replyMsg)) != 0) {
				printf("ERROR: During call to MsgReply! (%s, %d) --> Marking channel as not ready!\r\n",__FILE__, __LINE__);
				printf("ERRNO: %d (%s)\n", errno, strerror(errno));
				channel->ready = false;
			}
			break;
		default:
			break;
		}
	}
	return true;
}

/**
 * Call the function to close the channel.
 */
void channel_cleanup(channel_t* channel) {
	if (channel->server == NULL) {	// If it is a client side the server struct is NULL
		name_close(channel->server_coid);
	} else {	// otherwise it is a server
		name_detach(channel->server, 0);
	}
}
