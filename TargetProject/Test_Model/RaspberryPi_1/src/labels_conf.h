#ifndef LABELS_CONF_H_
#define LABELS_CONF_H_

#include "labels.h"

#define LABELS_COUNT	2

#define L_TMPLABEL 0
#define L_TMPLABEL2 1

/**
 * Label TMPLABEL
 */
#define L_TMPLABEL_SIZE 500000

extern uint8_t l_tmpLabel_dataA[L_TMPLABEL_SIZE];
extern uint8_t l_tmpLabel_dataB[L_TMPLABEL_SIZE];

extern globalLabel_t l_tmpLabel;

/**
 * Label TMPLABEL2
 */
#define L_TMPLABEL2_SIZE 1000

extern uint8_t l_tmpLabel2_dataA[L_TMPLABEL2_SIZE];
extern uint8_t l_tmpLabel2_dataB[L_TMPLABEL2_SIZE];

extern globalLabel_t l_tmpLabel2;



extern globalLabel_t* labels[LABELS_COUNT];

#endif //LABELS_CONF_H_
