/*
 * runnable.h
 *
 *  Created on: 15 Aug 2023
 *      Author: mabecker
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

#include "labels.h"

typedef struct runnable_spec runnable_spec_t;

/**
 * Pointer to a runnable execute function
 */
typedef void (*runnable_func_pointer)(runnable_spec_t*);


/**
 * Typedef for a runnable specification.
 */
typedef struct runnable_spec{

	int id;							// id of the runnable

	char* name;						// name of the runnable

	int cid;						// clock id if the thread the runnable executes in (to simulate execution)

	runnable_func_pointer func;		// runnable function

	runnable_func_pointer init;		// runnable initialization function

	runnable_func_pointer deinit;	// runnable deinitialization function

	bool initialized;				// flag to indicate if this runnable has been initialized

	int mode;						// mode the runnable is in

	void* user_data;				// User specific data for the runnable can be linked here

	double var;						// execution time variation in %

	/*------------------------------------------------------------------
	 * Data to manage the input labels
	 *----------------------------------------------------------------*/
	int inputLabelCount;			// number of input labels

	labelId_t* inputLabelIds;		// pointer to the array with all input label IDs

	localLabel_t** inputData;		// pointer to the array with all input label copies

	/*------------------------------------------------------------------
	 * Data to manage the output labels
	 *----------------------------------------------------------------*/
	int outputLabelCount;			// number of output labels

	labelId_t* outputLabelIds;		// pointer to the array with all output label IDs

	localLabel_t** outputData;		// pointer to the array with all output label copies

	// pointer to the next runnable in the list
	runnable_spec_t* next;
} runnable_spec_t;



#endif /* RUNNABLE_H_ */
