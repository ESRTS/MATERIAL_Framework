#ifndef LABELS_CONF_H_
#define LABELS_CONF_H_

#include "labels.h"

#define LABELS_COUNT	10

#define L_BRAKESIG 0
#define L_TORQUESIG 1
#define L_ABS_RR_SIG 2
#define L_ABS_RL_SIG 3
#define L_ABS_FR_SIG 4
#define L_ABS_FL_SIG 5
#define L_BRAKE_RR_SIG 6
#define L_BRAKE_RL_SIG 7
#define L_BRAKE_FL_SIG 8
#define L_BRAKE_FR_SIG 9

/**
 * Label BRAKESIG
 */
#define L_BRAKESIG_SIZE 2

extern uint8_t l_BrakeSig_dataA[L_BRAKESIG_SIZE];
extern uint8_t l_BrakeSig_dataB[L_BRAKESIG_SIZE];

extern globalLabel_t l_BrakeSig;

/**
 * Label TORQUESIG
 */
#define L_TORQUESIG_SIZE 2

extern uint8_t l_TorqueSig_dataA[L_TORQUESIG_SIZE];
extern uint8_t l_TorqueSig_dataB[L_TORQUESIG_SIZE];

extern globalLabel_t l_TorqueSig;

/**
 * Label ABS_RR_SIG
 */
#define L_ABS_RR_SIG_SIZE 2

extern uint8_t l_ABS_RR_Sig_dataA[L_ABS_RR_SIG_SIZE];
extern uint8_t l_ABS_RR_Sig_dataB[L_ABS_RR_SIG_SIZE];

extern globalLabel_t l_ABS_RR_Sig;

/**
 * Label ABS_RL_SIG
 */
#define L_ABS_RL_SIG_SIZE 2

extern uint8_t l_ABS_RL_Sig_dataA[L_ABS_RL_SIG_SIZE];
extern uint8_t l_ABS_RL_Sig_dataB[L_ABS_RL_SIG_SIZE];

extern globalLabel_t l_ABS_RL_Sig;

/**
 * Label ABS_FR_SIG
 */
#define L_ABS_FR_SIG_SIZE 2

extern uint8_t l_ABS_FR_Sig_dataA[L_ABS_FR_SIG_SIZE];
extern uint8_t l_ABS_FR_Sig_dataB[L_ABS_FR_SIG_SIZE];

extern globalLabel_t l_ABS_FR_Sig;

/**
 * Label ABS_FL_SIG
 */
#define L_ABS_FL_SIG_SIZE 2

extern uint8_t l_ABS_FL_Sig_dataA[L_ABS_FL_SIG_SIZE];
extern uint8_t l_ABS_FL_Sig_dataB[L_ABS_FL_SIG_SIZE];

extern globalLabel_t l_ABS_FL_Sig;

/**
 * Label BRAKE_RR_SIG
 */
#define L_BRAKE_RR_SIG_SIZE 2

extern uint8_t l_Brake_RR_Sig_dataA[L_BRAKE_RR_SIG_SIZE];
extern uint8_t l_Brake_RR_Sig_dataB[L_BRAKE_RR_SIG_SIZE];

extern globalLabel_t l_Brake_RR_Sig;

/**
 * Label BRAKE_RL_SIG
 */
#define L_BRAKE_RL_SIG_SIZE 2

extern uint8_t l_Brake_RL_Sig_dataA[L_BRAKE_RL_SIG_SIZE];
extern uint8_t l_Brake_RL_Sig_dataB[L_BRAKE_RL_SIG_SIZE];

extern globalLabel_t l_Brake_RL_Sig;

/**
 * Label BRAKE_FL_SIG
 */
#define L_BRAKE_FL_SIG_SIZE 2

extern uint8_t l_Brake_FL_Sig_dataA[L_BRAKE_FL_SIG_SIZE];
extern uint8_t l_Brake_FL_Sig_dataB[L_BRAKE_FL_SIG_SIZE];

extern globalLabel_t l_Brake_FL_Sig;

/**
 * Label BRAKE_FR_SIG
 */
#define L_BRAKE_FR_SIG_SIZE 2

extern uint8_t l_Brake_FR_Sig_dataA[L_BRAKE_FR_SIG_SIZE];
extern uint8_t l_Brake_FR_Sig_dataB[L_BRAKE_FR_SIG_SIZE];

extern globalLabel_t l_Brake_FR_Sig;



extern globalLabel_t* labels[LABELS_COUNT];

#endif //LABELS_CONF_H_
