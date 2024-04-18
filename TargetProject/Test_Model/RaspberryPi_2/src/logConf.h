/*
 * logConf.h
 *
 *  Created on: 29 Mar 2023
 *      Author: mabecker
 */

#ifndef LOGCONF_H_
#define LOGCONF_H_

/**
 * Enable for logging and error messages for the labels module.
 */
#define PRINT_LABELS_INFO_MSG
#define PRINT_LABELS_ERROR_MSG

/**
 * Enable for logging and error messages for the thread module.
 */
#define PRINT_THREAD_INFO_MSG
#define PRINT_THREAD_ERROR_MSG

/**
 * Enable for logging and error messages for the time functions.
 */
#define PRINT_TIME_INFO_MSG
#define PRINT_TIME_ERROR_MSG

/**
 * Enable for logging and error messages for the network communication functions.
 */
//#define PRINT_COM_INFO_MSG
#define PRINT_COM_ERROR_MSG

/**
 * Enable for logging and error messages for the static network communication functions.
 */
#define PRINT_COMSTATIC_INFO_MSG
#define PRINT_COMSTATIC_ERROR_MSG

/**
 * Enable for logging and error messages for the node manager.
 */
//#define MAN_INFO_MSG
#define MAN_PRINT_ERROR_MSG

#endif /* LOGCONF_H_ */
