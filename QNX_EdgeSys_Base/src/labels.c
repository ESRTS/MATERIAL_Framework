/*
 * labels.c
 *
 *  Created on: 28 Mar 2023
 *      Author: Matthias Becker
 */
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "labels.h"
#include "logConf.h"
#include "labels_conf.h"


#ifdef PRINT_LABELS_INFO_MSG
  #define LABELS_PRINT_INFO( fmt, ...) fprintf( stdout, "[LABELS] " fmt "\r\n", ##__VA_ARGS__)
#else
  #define LABELS_PRINT_INFO(fmt, ...)
#endif


#ifdef PRINT_LABELS_ERROR_MSG
  #define LABELS_PRINT_ERROR( fmt, ...) fprintf( stdout, "[LABELS ERROR]" fmt " [%s:%d]\r\n", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
  #define LABELS_PRINT_ERROR( fmt, ...)
#endif

/**
 * Label helper
 */
static atomic_int labelSlotA = 0;
static atomic_int labelSlotB = 1;

/**
 * Private array for all labels of the node
 */
//globalLabel_t labels[LABELS_COUNT];



/**
 * Flag to indicate if the labels are initialized
 */
static bool initialized = false;

/**
 * The function initializes all label data.
 */
uint32_t label_init(void) {

	// Set all labels to a defined state
	for (int i = 0; i < LABELS_COUNT; i++) {

		atomic_store_explicit(&labels[i]->readpos, labelSlotA, memory_order_seq_cst);

		memset(labels[i]->dataA, 0 , labels[i]->size);
		memset(labels[i]->dataB, 0 , labels[i]->size);
	}

	initialized = true;
	return EOK;
}

/**
 * The function updates the content of local_label with the label
 * current value of the global label with labelId.
 */
void label_read(labelId_t labelId, localLabel_t* local_label) {
	if (!initialized) {
		LABELS_PRINT_ERROR("Labels not initialized!");
		return;
	}

	atomic_int index = atomic_load_explicit(&labels[labelId]->readpos, memory_order_seq_cst);	// Find which buffer to read

	if (index == 0) {
		memcpy(local_label->data, labels[labelId]->dataA, local_label->size);					// Read buffer A
	} else if (index == 1) {
		memcpy(local_label->data, labels[labelId]->dataB, local_label->size);					// Read buffer B
	}
}

/**
 * The function copies the content of the local_label to the
 * global label with labelId.
 */
void label_write(labelId_t labelId, localLabel_t* local_label) {
	if (!initialized) {
		LABELS_PRINT_ERROR("Labels not initialized!");
		return;
	}

	atomic_int index = atomic_load_explicit(&labels[labelId]->readpos, memory_order_seq_cst);	// Find which buffer was written last

	if (index == 0) {
		memcpy(labels[labelId]->dataB, local_label->data, local_label->size);					// A was written last, so now write to B
		atomic_store_explicit(&labels[labelId]->readpos, labelSlotB, memory_order_seq_cst);
	} else if (index== 1) {
		memcpy(labels[labelId]->dataA, local_label->data, local_label->size);					// B was written last, so now write to A
		atomic_store_explicit(&labels[labelId]->readpos, labelSlotA, memory_order_seq_cst);
	}
}
