/*
 * channel_conf.h
 *
 * THIS FILE IS GENERATED! 
 * DON'T MODIFY BY HAND!
 */

#ifndef CHANNEL_CONF_H_
#define CHANNEL_CONF_H_

#include "channel.h"

/**
 * Type used for the messages that are passed between pGlobalBrakeController_to_RaspberryPi_2
 */
typedef struct {

	msg_common_t common;		// Message header used by QNX

	uint8_t payload[8];		// Pointer to the payload

} pGlobalBrakeController_to_RaspberryPi_2_t;

#endif /* CHANNEL_CONF_H_ */
