/*
 * stat.c
 *
 *  Created on: 20 Aug 2023
 *      Author: mabecker
 */

#include "stat.h"

/**
 * Function handles min/max/avrg of the value
 */
void stat_new_value(stat_t* stat, uint64_t val) {

	if (!stat->init) {	// Do the initialization exactly one
		stat->min = UINT64_MAX;
		stat->max = 0;
		stat->avrg = 0;
		stat->init = true;
	}

	if (stat->min > val) stat->min = val;
	if (stat->max < val) stat->max = val;

	stat->avrg = ((stat->n * stat->avrg) + val) / (stat->n + 1);

#ifdef STAT_COLLECT_SAMPLES
	// In this mode we collect every value we observe
	stat->samples[stat->n] = val;
#endif

	stat->n++;
}


