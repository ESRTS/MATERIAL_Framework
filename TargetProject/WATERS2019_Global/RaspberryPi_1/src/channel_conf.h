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
 * Type used for the messages that are passed between Lidar_to_RaspberryPi_2
 */
typedef struct {

	msg_common_t common;		// Message header used by QNX

	uint8_t payload[500000];		// Pointer to the payload

} Lidar_to_RaspberryPi_2_t;

/**
 * Type used for the messages that are passed between EKF_to_RaspberryPi_2
 */
typedef struct {

	msg_common_t common;		// Message header used by QNX

	uint8_t payload[5000];		// Pointer to the payload

} EKF_to_RaspberryPi_2_t;

/**
 * Type used for the messages that are passed between Detection_to_RaspberryPi_2
 */
typedef struct {

	msg_common_t common;		// Message header used by QNX

	uint8_t payload[750000];		// Pointer to the payload

} Detection_to_RaspberryPi_2_t;

/**
 * Type used for the messages that are passed between Localization_to_RaspberryPi_2
 */
typedef struct {

	msg_common_t common;		// Message header used by QNX

	uint8_t payload[3000];		// Pointer to the payload

} Localization_to_RaspberryPi_2_t;

#endif /* CHANNEL_CONF_H_ */
