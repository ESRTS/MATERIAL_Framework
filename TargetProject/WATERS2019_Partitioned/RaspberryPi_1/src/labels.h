/*
 * labels.h
 *
 *  Created on: 28 Mar 2023
 *      Author: Matthias Becker
 */

#ifndef LABELS_H_
#define LABELS_H_

#include <stdint.h>
#include <stdatomic.h>

/**
 * Type to refer to label IDs
 */
typedef uint32_t labelId_t;

/**
 * Type used for all global labels
 */
typedef struct globallabel {
	atomic_int 	readpos;	// read position currently used
	uint8_t*	dataA;		// pointer to the data A
	uint8_t*	dataB;		// pointer to the data B
	int 		size;		// size of the label in bytes
} globalLabel_t;

/**
 * Type used for all local labels
 */
typedef struct locallabel {
	uint8_t*	data;		// pointer to the data B
	int 		size;		// size of the label in bytes
} localLabel_t;

/**
 * The function initializes all label data.
 */
uint32_t label_init(void);

/**
 * The function updates the content of local_label with the label
 * current value of the global label with labelId.
 */
void label_read(labelId_t labelId, localLabel_t* local_label);

/**
 * The function copies the content of the local_label to the
 * global label with labelId.
 */
void label_write(labelId_t labelId, localLabel_t* local_label);

#endif /* LABELS_H_ */
