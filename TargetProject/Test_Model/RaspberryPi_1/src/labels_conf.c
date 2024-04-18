#include "labels_conf.h"

/**
 * Label TMPLABEL
 */

uint8_t l_tmpLabel_dataA[L_TMPLABEL_SIZE];
uint8_t l_tmpLabel_dataB[L_TMPLABEL_SIZE];

globalLabel_t l_tmpLabel = {
	.readpos = 0,
	.dataA = l_tmpLabel_dataA,
	.dataB = l_tmpLabel_dataB,
	.size = L_TMPLABEL_SIZE
};

/**
 * Label TMPLABEL2
 */

uint8_t l_tmpLabel2_dataA[L_TMPLABEL2_SIZE];
uint8_t l_tmpLabel2_dataB[L_TMPLABEL2_SIZE];

globalLabel_t l_tmpLabel2 = {
	.readpos = 0,
	.dataA = l_tmpLabel2_dataA,
	.dataB = l_tmpLabel2_dataB,
	.size = L_TMPLABEL2_SIZE
};



globalLabel_t* labels[LABELS_COUNT] = {
	&l_tmpLabel,
	&l_tmpLabel2,
};

