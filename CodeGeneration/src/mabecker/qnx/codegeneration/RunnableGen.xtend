package mabecker.qnx.codegeneration

import java.util.ArrayList

import mabecker.qnx.codegeneration.model.QnxRunnable
import mabecker.qnx.codegeneration.model.QnxNode
import mabecker.qnx.codegeneration.model.QnxRunnableType

class RunnableGen {
	
	/**
	 * Method generates the header file
	 */
	static def generateHeader(ArrayList<QnxRunnable> runnables) {
		'''
			#ifndef USER_RUNNABLES_H
			#define USER_RUNNABLES_H
			
			/**
			 * Function prototypes for all runnables
			 */
			
			«FOR r : runnables»
				/* Functions for Runnable «r.name» */
				void r_«r.name»_init(runnable_spec_t* spec);
				void r_«r.name»(runnable_spec_t* spec);
				void r_«r.name»_deinit(runnable_spec_t* spec);
				
			«ENDFOR»
			«FOR r : runnables»
				/**************************************************************************
				 * Runnable «r.name» configuration
				 *************************************************************************/
				«IF r.readLabels.size > 0»
					/**** READ ****/
					#define 		«toUpper(r.name)»_READ_COUNT		«r.readLabels.size»
					labelId_t 	«r.name»_R_labelIds[«toUpper(r.name)»_READ_COUNT] = {«Generator.generateLabelString(r.readLabels)»};
					
					«FOR l : r.readLabels»
						uint8_t r_«r.name»_«l.name»_buffer[L_«toUpper(l.name)»_SIZE];	// Local buffer for label «r.name»
						localLabel_t r_«r.name»_«l.name» = {
							.data = r_«r.name»_«l.name»_buffer,
							.size = L_«toUpper(l.name)»_SIZE
						};
						
					«ENDFOR»
					
					localLabel_t* «r.name»_R_copies[«toUpper(r.name)»_READ_COUNT] = {
						«FOR l : r.readLabels»
							&r_«r.name»_«l.name»,
						«ENDFOR»
					};
					
				«ENDIF»
				«IF r.writeLabels.size > 0»
					/**** WRITE ****/
					#define 		«toUpper(r.name)»_WRITE_COUNT	«r.writeLabels.size»
					labelId_t 	«r.name»_W_labelIds[«toUpper(r.name)»_WRITE_COUNT] = {«Generator.generateLabelString(r.writeLabels)»};
					
					«FOR l : r.writeLabels»
						uint8_t w_«r.name»_«l.name»_buffer[L_«toUpper(l.name)»_SIZE];	// Local buffer for label «r.name»
						localLabel_t w_«r.name»_«l.name» = {
							.data = w_«r.name»_«l.name»_buffer,
							.size = L_«toUpper(l.name)»_SIZE
						};
					«ENDFOR»
					
					localLabel_t* «r.name»_W_copies[«toUpper(r.name)»_WRITE_COUNT] = {
						«FOR l : r.writeLabels»
							&w_«r.name»_«l.name»,
						«ENDFOR»
					};
				«ENDIF»
				
				/**** CONFIGURATION ****/
				runnable_spec_t «r.name» = {
					.name = "«r.name»",
					.func = r_«r.name»,
					.init = r_«r.name»_init,
					.deinit = r_«r.name»_deinit,
					.initialized = false,
					.mode = «r.baseMode»,
					.var = 0.0,
					.user_data = NULL,
					«IF r.readLabels.size > 0»
						.inputLabelCount = «toUpper(r.name)»_READ_COUNT,
						.inputLabelIds = «r.name»_R_labelIds,
						.inputData = «r.name»_R_copies,
					«ELSE»
						.inputLabelCount = 0,
						.inputLabelIds = NULL,
						.inputData = NULL,
					«ENDIF»
					«IF r.writeLabels.size > 0»
						.outputLabelCount = «toUpper(r.name)»_WRITE_COUNT,
						.outputLabelIds = «r.name»_W_labelIds,
						.outputData = «r.name»_W_copies
					«ELSE»
						.outputLabelCount = 0,
						.outputLabelIds = NULL,
						.outputData = NULL
					«ENDIF»
				};
				
			 «ENDFOR»
			#endif //USER_RUNNABLES_H
		'''
	}
	
	/**
	 * Method generates the code for each thread
	 */
	static def generateSrc(ArrayList<QnxRunnable> runnables, QnxNode node) {
		'''
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
				 
			«FOR r : runnables»
				«IF r.type == QnxRunnableType.USER_RUNNABLE»
					/**
					 * Generated initialization function for runnable «r.name»
					 */
					__attribute__((weak)) void r_«r.name»_init(runnable_spec_t* spec) {
						printf("[Runnable] Initializing %s\r\n", spec->name);
						
						spec->initialized = true;
					}
					
					/**
					 * Generated implementation for runnable «r.name»
					 */
					__attribute__((weak)) void r_«r.name»(runnable_spec_t* spec) {
						
						/**
						 * Simulate the execution
						 */
						switch (spec->mode) {
							«FOR mode : r.modes»
								case «mode.condition»:
									burn_cycles(«r.getExecTime_us(r.modes.indexOf(mode), node)», spec->cid); // Execute for «r.getExecTime_us(r.modes.indexOf(mode), node)» us
									break;
							«ENDFOR»
							default:
								return;
						}
					}
					
					/**
					 * Generated deinitialization function for runnable «r.name»
					 */
					__attribute__((weak)) void r_«r.name»_deinit(runnable_spec_t* spec) {
						printf("[Runnable] Deinitializing %s\r\n", spec->name);
						
						spec->initialized = false;
					}
				«ENDIF»
				«IF r.type == QnxRunnableType.SENDER_RUNNABLE»
					/**
					 * Generated initialization function for runnable «r.name»
					 * This is a communication runnable (sender) and should not be changed!
					 */
					void r_«r.name»_init(runnable_spec_t* spec) {
						printf("[Runnable] Initializing %s\r\n", spec->name);
							
						channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
						
						channel->msg = (void*)malloc(sizeof(«r.channel.name»_t));	// Allocate the memory to temporarily store a message
						
						if (channel != NULL) {
							spec->user_data = channel;	// Link the channel struct to the runnable struct
						
							channel->name = "«r.channel.name»_channel";
							channel->server_coid = -1;
							channel->server = NULL;
						
							channel_connect(channel);
						
							spec->initialized = true;
						}
					}
					
					/**
					 * Generated implementation for runnable «r.name»
					 * This is a communication runnable (sender) and should not be changed!
					 */
					void r_«r.name»(runnable_spec_t* spec) {
					
						channel_t* channel = (channel_t*)spec->user_data;	// get the channel data
					
						«r.channel.name»_t* msg = channel->msg;
						msg->common.hdr.type = CHANNEL_MSG_TYPE;
					
						uint8_t* writePointer = msg->payload;
					
						/* Fill the payload section of the message with all label data */
						for (int i = 0; i < spec->inputLabelCount; i++) {
							memcpy(writePointer, spec->inputData[i]->data, spec->inputData[i]->size);	// Copy the label to the msg payload
							writePointer += spec->inputData[i]->size;									// Move the write pointer after the label we just wrote
						}
					
						channel_send(channel, (uint8_t*)msg, sizeof(«r.channel.name»_t));	// Send the message to the server
					}
					
					/**
					 * Generated deinitialization function for runnable «r.name»
					 * This is a communication runnable (sender) and should not be changed!
					 */
					void r_«r.name»_deinit(runnable_spec_t* spec) {
						printf("[Runnable] Deinitializing %s\r\n", spec->name);
						
						channel_cleanup((channel_t*)spec->user_data);
						
						spec->initialized = false;
					}
				«ENDIF»
				«IF r.type == QnxRunnableType.RECEIVER_RUNNABLE»
					/**
					 * Generated initialization function for runnable «r.name»
					 * This is a communication runnable (receiver) and should not be changed!
					 */
					void r_«r.name»_init(runnable_spec_t* spec) {
						printf("[Runnable] Initializing %s\r\n", spec->name);
													
						channel_t* channel = (channel_t*)malloc(sizeof(channel_t));	// Allocate memory for the new channel
						
						channel->msg = (void*)malloc(sizeof(«r.channel.name»_t));	// Allocate the memory to temporarily store a message
						
						if (channel != NULL) {
							spec->user_data = channel;	// Link the channel struct to the runnable struct
					
							channel->name = "«r.channel.name»_channel";
							channel->server_coid = -1;
							channel->server = NULL;
							
							channel_create(channel);
					
							spec->initialized = true;
						}
					}
					
					/**
					 * Generated implementation for runnable «r.name»
					 * This is a communication runnable (receiver) and should not be changed!
					 */
					void r_«r.name»(runnable_spec_t* spec) {
						channel_t* channel = (channel_t*)spec->user_data;	// get the channel data
						
						«r.channel.name»_t* msg = channel->msg;
						
						if (channel_receive(channel, (uint8_t*)msg, sizeof(«r.channel.name»_t)) == true) {							// Receive data on the channel
						
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
					 * Generated deinitialization function for runnable «r.name»
					 * This is a communication runnable (receiver) and should not be changed!
					 */
					void r_«r.name»_deinit(runnable_spec_t* spec) {
						printf("[Runnable] Deinitializing %s\r\n", spec->name);
						
						channel_cleanup((channel_t*)spec->user_data);
						
						spec->initialized = false;
					}
				«ENDIF»
				
			«ENDFOR»
		'''
	}
	
	/**
	 * Helper method to create strings with all upper case letters.
	 */
	static def toUpper(String s) {
		return s.toUpperCase;
	}
	
}
