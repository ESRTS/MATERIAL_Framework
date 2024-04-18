/*
 * stat.h
 *
 *  Created on: 20 Aug 2023
 *      Author: mabecker
 */

#ifndef STAT_H_
#define STAT_H_

#include <inttypes.h>
#include <stdbool.h>

//#define STAT_COLLECT_SAMPLES

/**
 * Define the number of samples that we can collect in sample collection mode
 */
#define STAT_MAX_SAMPLES (100 * 30)
/**
 * Data structure for one runtime statistic
 */
typedef struct {

	// Flag to indicate that this structure is initialized
	bool init;

	// Minimum observed value
	uint64_t min;

	// Maximum observed value
	uint64_t max;

	// Average observed value
	uint64_t avrg;

	// Number of samples for the average value
	uint64_t n;
#ifdef STAT_COLLECT_SAMPLES
	uint64_t samples[STAT_MAX_SAMPLES];
#endif
} stat_t;

void stat_new_value(stat_t* stat, uint64_t val);

#endif /* STAT_H_ */
