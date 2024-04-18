#include "labels_conf.h"

/**
 * Label BRAKESIG
 */

uint8_t l_BrakeSig_dataA[L_BRAKESIG_SIZE];
uint8_t l_BrakeSig_dataB[L_BRAKESIG_SIZE];

globalLabel_t l_BrakeSig = {
	.readpos = 0,
	.dataA = l_BrakeSig_dataA,
	.dataB = l_BrakeSig_dataB,
	.size = L_BRAKESIG_SIZE
};

/**
 * Label TORQUESIG
 */

uint8_t l_TorqueSig_dataA[L_TORQUESIG_SIZE];
uint8_t l_TorqueSig_dataB[L_TORQUESIG_SIZE];

globalLabel_t l_TorqueSig = {
	.readpos = 0,
	.dataA = l_TorqueSig_dataA,
	.dataB = l_TorqueSig_dataB,
	.size = L_TORQUESIG_SIZE
};

/**
 * Label ABS_RR_SIG
 */

uint8_t l_ABS_RR_Sig_dataA[L_ABS_RR_SIG_SIZE];
uint8_t l_ABS_RR_Sig_dataB[L_ABS_RR_SIG_SIZE];

globalLabel_t l_ABS_RR_Sig = {
	.readpos = 0,
	.dataA = l_ABS_RR_Sig_dataA,
	.dataB = l_ABS_RR_Sig_dataB,
	.size = L_ABS_RR_SIG_SIZE
};

/**
 * Label ABS_RL_SIG
 */

uint8_t l_ABS_RL_Sig_dataA[L_ABS_RL_SIG_SIZE];
uint8_t l_ABS_RL_Sig_dataB[L_ABS_RL_SIG_SIZE];

globalLabel_t l_ABS_RL_Sig = {
	.readpos = 0,
	.dataA = l_ABS_RL_Sig_dataA,
	.dataB = l_ABS_RL_Sig_dataB,
	.size = L_ABS_RL_SIG_SIZE
};

/**
 * Label ABS_FR_SIG
 */

uint8_t l_ABS_FR_Sig_dataA[L_ABS_FR_SIG_SIZE];
uint8_t l_ABS_FR_Sig_dataB[L_ABS_FR_SIG_SIZE];

globalLabel_t l_ABS_FR_Sig = {
	.readpos = 0,
	.dataA = l_ABS_FR_Sig_dataA,
	.dataB = l_ABS_FR_Sig_dataB,
	.size = L_ABS_FR_SIG_SIZE
};

/**
 * Label ABS_FL_SIG
 */

uint8_t l_ABS_FL_Sig_dataA[L_ABS_FL_SIG_SIZE];
uint8_t l_ABS_FL_Sig_dataB[L_ABS_FL_SIG_SIZE];

globalLabel_t l_ABS_FL_Sig = {
	.readpos = 0,
	.dataA = l_ABS_FL_Sig_dataA,
	.dataB = l_ABS_FL_Sig_dataB,
	.size = L_ABS_FL_SIG_SIZE
};

/**
 * Label BRAKE_RR_SIG
 */

uint8_t l_Brake_RR_Sig_dataA[L_BRAKE_RR_SIG_SIZE];
uint8_t l_Brake_RR_Sig_dataB[L_BRAKE_RR_SIG_SIZE];

globalLabel_t l_Brake_RR_Sig = {
	.readpos = 0,
	.dataA = l_Brake_RR_Sig_dataA,
	.dataB = l_Brake_RR_Sig_dataB,
	.size = L_BRAKE_RR_SIG_SIZE
};

/**
 * Label BRAKE_RL_SIG
 */

uint8_t l_Brake_RL_Sig_dataA[L_BRAKE_RL_SIG_SIZE];
uint8_t l_Brake_RL_Sig_dataB[L_BRAKE_RL_SIG_SIZE];

globalLabel_t l_Brake_RL_Sig = {
	.readpos = 0,
	.dataA = l_Brake_RL_Sig_dataA,
	.dataB = l_Brake_RL_Sig_dataB,
	.size = L_BRAKE_RL_SIG_SIZE
};

/**
 * Label BRAKE_FL_SIG
 */

uint8_t l_Brake_FL_Sig_dataA[L_BRAKE_FL_SIG_SIZE];
uint8_t l_Brake_FL_Sig_dataB[L_BRAKE_FL_SIG_SIZE];

globalLabel_t l_Brake_FL_Sig = {
	.readpos = 0,
	.dataA = l_Brake_FL_Sig_dataA,
	.dataB = l_Brake_FL_Sig_dataB,
	.size = L_BRAKE_FL_SIG_SIZE
};

/**
 * Label BRAKE_FR_SIG
 */

uint8_t l_Brake_FR_Sig_dataA[L_BRAKE_FR_SIG_SIZE];
uint8_t l_Brake_FR_Sig_dataB[L_BRAKE_FR_SIG_SIZE];

globalLabel_t l_Brake_FR_Sig = {
	.readpos = 0,
	.dataA = l_Brake_FR_Sig_dataA,
	.dataB = l_Brake_FR_Sig_dataB,
	.size = L_BRAKE_FR_SIG_SIZE
};



globalLabel_t* labels[LABELS_COUNT] = {
	&l_BrakeSig,
	&l_TorqueSig,
	&l_ABS_RR_Sig,
	&l_ABS_RL_Sig,
	&l_ABS_FR_Sig,
	&l_ABS_FL_Sig,
	&l_Brake_RR_Sig,
	&l_Brake_RL_Sig,
	&l_Brake_FL_Sig,
	&l_Brake_FR_Sig,
};

