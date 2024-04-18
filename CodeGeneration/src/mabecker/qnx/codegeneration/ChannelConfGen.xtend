package mabecker.qnx.codegeneration

import java.util.ArrayList
import mabecker.qnx.codegeneration.model.QnxComChannel

class ChannelConfGen {
	
	static def generateHeader(ArrayList<QnxComChannel> channels) {
		'''
		/*
		 * channel_conf.h
		 *
		 * THIS FILE IS GENERATED! 
		 * DON'T MODIFY BY HAND!
		 */
		
		#ifndef CHANNEL_CONF_H_
		#define CHANNEL_CONF_H_
		
		#include "channel.h"
		
		«FOR channel : channels»
		/**
		 * Type used for the messages that are passed between «channel.name»
		 */
		typedef struct {
		
			msg_common_t common;		// Message header used by QNX
		
			uint8_t payload[«channel.payloadSizeByte»];		// Pointer to the payload
		
		} «channel.name»_t;
		
		«ENDFOR»
		#endif /* CHANNEL_CONF_H_ */
		'''
	}
}