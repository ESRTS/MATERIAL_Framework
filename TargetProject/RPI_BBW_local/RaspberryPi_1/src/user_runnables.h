#ifndef USER_RUNNABLES_H
#define USER_RUNNABLES_H

/**
 * Function prototypes for all runnables
 */

/* Functions for Runnable ABS_FL_T */
void r_ABS_FL_T_init(runnable_spec_t* spec);
void r_ABS_FL_T(runnable_spec_t* spec);
void r_ABS_FL_T_deinit(runnable_spec_t* spec);

/* Functions for Runnable BrakeActuator_FL_LDM */
void r_BrakeActuator_FL_LDM_init(runnable_spec_t* spec);
void r_BrakeActuator_FL_LDM(runnable_spec_t* spec);
void r_BrakeActuator_FL_LDM_deinit(runnable_spec_t* spec);

/* Functions for Runnable ABS_FR_T */
void r_ABS_FR_T_init(runnable_spec_t* spec);
void r_ABS_FR_T(runnable_spec_t* spec);
void r_ABS_FR_T_deinit(runnable_spec_t* spec);

/* Functions for Runnable BrakeActuator_FR_LDM */
void r_BrakeActuator_FR_LDM_init(runnable_spec_t* spec);
void r_BrakeActuator_FR_LDM(runnable_spec_t* spec);
void r_BrakeActuator_FR_LDM_deinit(runnable_spec_t* spec);

/* Functions for Runnable ABS_RL_T */
void r_ABS_RL_T_init(runnable_spec_t* spec);
void r_ABS_RL_T(runnable_spec_t* spec);
void r_ABS_RL_T_deinit(runnable_spec_t* spec);

/* Functions for Runnable BrakeActuator_RL_LDM */
void r_BrakeActuator_RL_LDM_init(runnable_spec_t* spec);
void r_BrakeActuator_RL_LDM(runnable_spec_t* spec);
void r_BrakeActuator_RL_LDM_deinit(runnable_spec_t* spec);

/* Functions for Runnable ABS_RR_T */
void r_ABS_RR_T_init(runnable_spec_t* spec);
void r_ABS_RR_T(runnable_spec_t* spec);
void r_ABS_RR_T_deinit(runnable_spec_t* spec);

/* Functions for Runnable BrakeActuator_RR_LDM */
void r_BrakeActuator_RR_LDM_init(runnable_spec_t* spec);
void r_BrakeActuator_RR_LDM(runnable_spec_t* spec);
void r_BrakeActuator_RR_LDM_deinit(runnable_spec_t* spec);

/* Functions for Runnable BrakePedalLDM_T */
void r_BrakePedalLDM_T_init(runnable_spec_t* spec);
void r_BrakePedalLDM_T(runnable_spec_t* spec);
void r_BrakePedalLDM_T_deinit(runnable_spec_t* spec);

/* Functions for Runnable BrakeTorqMap */
void r_BrakeTorqMap_init(runnable_spec_t* spec);
void r_BrakeTorqMap(runnable_spec_t* spec);
void r_BrakeTorqMap_deinit(runnable_spec_t* spec);

/* Functions for Runnable GlobalBrakeController */
void r_GlobalBrakeController_init(runnable_spec_t* spec);
void r_GlobalBrakeController(runnable_spec_t* spec);
void r_GlobalBrakeController_deinit(runnable_spec_t* spec);

/**************************************************************************
 * Runnable ABS_FL_T configuration
 *************************************************************************/
/**** READ ****/
#define 		ABS_FL_T_READ_COUNT		1
labelId_t 	ABS_FL_T_R_labelIds[ABS_FL_T_READ_COUNT] = {L_ABS_FL_SIG};

uint8_t r_ABS_FL_T_ABS_FL_Sig_buffer[L_ABS_FL_SIG_SIZE];	// Local buffer for label ABS_FL_T
localLabel_t r_ABS_FL_T_ABS_FL_Sig = {
	.data = r_ABS_FL_T_ABS_FL_Sig_buffer,
	.size = L_ABS_FL_SIG_SIZE
};


localLabel_t* ABS_FL_T_R_copies[ABS_FL_T_READ_COUNT] = {
	&r_ABS_FL_T_ABS_FL_Sig,
};

/**** WRITE ****/
#define 		ABS_FL_T_WRITE_COUNT	1
labelId_t 	ABS_FL_T_W_labelIds[ABS_FL_T_WRITE_COUNT] = {L_BRAKE_FL_SIG};

uint8_t w_ABS_FL_T_Brake_FL_Sig_buffer[L_BRAKE_FL_SIG_SIZE];	// Local buffer for label ABS_FL_T
localLabel_t w_ABS_FL_T_Brake_FL_Sig = {
	.data = w_ABS_FL_T_Brake_FL_Sig_buffer,
	.size = L_BRAKE_FL_SIG_SIZE
};

localLabel_t* ABS_FL_T_W_copies[ABS_FL_T_WRITE_COUNT] = {
	&w_ABS_FL_T_Brake_FL_Sig,
};

/**** CONFIGURATION ****/
runnable_spec_t ABS_FL_T = {
	.name = "ABS_FL_T",
	.func = r_ABS_FL_T,
	.init = r_ABS_FL_T_init,
	.deinit = r_ABS_FL_T_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = ABS_FL_T_READ_COUNT,
	.inputLabelIds = ABS_FL_T_R_labelIds,
	.inputData = ABS_FL_T_R_copies,
	.outputLabelCount = ABS_FL_T_WRITE_COUNT,
	.outputLabelIds = ABS_FL_T_W_labelIds,
	.outputData = ABS_FL_T_W_copies
};

/**************************************************************************
 * Runnable BrakeActuator_FL_LDM configuration
 *************************************************************************/
/**** READ ****/
#define 		BRAKEACTUATOR_FL_LDM_READ_COUNT		1
labelId_t 	BrakeActuator_FL_LDM_R_labelIds[BRAKEACTUATOR_FL_LDM_READ_COUNT] = {L_BRAKE_FL_SIG};

uint8_t r_BrakeActuator_FL_LDM_Brake_FL_Sig_buffer[L_BRAKE_FL_SIG_SIZE];	// Local buffer for label BrakeActuator_FL_LDM
localLabel_t r_BrakeActuator_FL_LDM_Brake_FL_Sig = {
	.data = r_BrakeActuator_FL_LDM_Brake_FL_Sig_buffer,
	.size = L_BRAKE_FL_SIG_SIZE
};


localLabel_t* BrakeActuator_FL_LDM_R_copies[BRAKEACTUATOR_FL_LDM_READ_COUNT] = {
	&r_BrakeActuator_FL_LDM_Brake_FL_Sig,
};


/**** CONFIGURATION ****/
runnable_spec_t BrakeActuator_FL_LDM = {
	.name = "BrakeActuator_FL_LDM",
	.func = r_BrakeActuator_FL_LDM,
	.init = r_BrakeActuator_FL_LDM_init,
	.deinit = r_BrakeActuator_FL_LDM_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = BRAKEACTUATOR_FL_LDM_READ_COUNT,
	.inputLabelIds = BrakeActuator_FL_LDM_R_labelIds,
	.inputData = BrakeActuator_FL_LDM_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable ABS_FR_T configuration
 *************************************************************************/
/**** READ ****/
#define 		ABS_FR_T_READ_COUNT		1
labelId_t 	ABS_FR_T_R_labelIds[ABS_FR_T_READ_COUNT] = {L_ABS_FR_SIG};

uint8_t r_ABS_FR_T_ABS_FR_Sig_buffer[L_ABS_FR_SIG_SIZE];	// Local buffer for label ABS_FR_T
localLabel_t r_ABS_FR_T_ABS_FR_Sig = {
	.data = r_ABS_FR_T_ABS_FR_Sig_buffer,
	.size = L_ABS_FR_SIG_SIZE
};


localLabel_t* ABS_FR_T_R_copies[ABS_FR_T_READ_COUNT] = {
	&r_ABS_FR_T_ABS_FR_Sig,
};

/**** WRITE ****/
#define 		ABS_FR_T_WRITE_COUNT	1
labelId_t 	ABS_FR_T_W_labelIds[ABS_FR_T_WRITE_COUNT] = {L_BRAKE_FR_SIG};

uint8_t w_ABS_FR_T_Brake_FR_Sig_buffer[L_BRAKE_FR_SIG_SIZE];	// Local buffer for label ABS_FR_T
localLabel_t w_ABS_FR_T_Brake_FR_Sig = {
	.data = w_ABS_FR_T_Brake_FR_Sig_buffer,
	.size = L_BRAKE_FR_SIG_SIZE
};

localLabel_t* ABS_FR_T_W_copies[ABS_FR_T_WRITE_COUNT] = {
	&w_ABS_FR_T_Brake_FR_Sig,
};

/**** CONFIGURATION ****/
runnable_spec_t ABS_FR_T = {
	.name = "ABS_FR_T",
	.func = r_ABS_FR_T,
	.init = r_ABS_FR_T_init,
	.deinit = r_ABS_FR_T_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = ABS_FR_T_READ_COUNT,
	.inputLabelIds = ABS_FR_T_R_labelIds,
	.inputData = ABS_FR_T_R_copies,
	.outputLabelCount = ABS_FR_T_WRITE_COUNT,
	.outputLabelIds = ABS_FR_T_W_labelIds,
	.outputData = ABS_FR_T_W_copies
};

/**************************************************************************
 * Runnable BrakeActuator_FR_LDM configuration
 *************************************************************************/
/**** READ ****/
#define 		BRAKEACTUATOR_FR_LDM_READ_COUNT		1
labelId_t 	BrakeActuator_FR_LDM_R_labelIds[BRAKEACTUATOR_FR_LDM_READ_COUNT] = {L_BRAKE_FR_SIG};

uint8_t r_BrakeActuator_FR_LDM_Brake_FR_Sig_buffer[L_BRAKE_FR_SIG_SIZE];	// Local buffer for label BrakeActuator_FR_LDM
localLabel_t r_BrakeActuator_FR_LDM_Brake_FR_Sig = {
	.data = r_BrakeActuator_FR_LDM_Brake_FR_Sig_buffer,
	.size = L_BRAKE_FR_SIG_SIZE
};


localLabel_t* BrakeActuator_FR_LDM_R_copies[BRAKEACTUATOR_FR_LDM_READ_COUNT] = {
	&r_BrakeActuator_FR_LDM_Brake_FR_Sig,
};


/**** CONFIGURATION ****/
runnable_spec_t BrakeActuator_FR_LDM = {
	.name = "BrakeActuator_FR_LDM",
	.func = r_BrakeActuator_FR_LDM,
	.init = r_BrakeActuator_FR_LDM_init,
	.deinit = r_BrakeActuator_FR_LDM_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = BRAKEACTUATOR_FR_LDM_READ_COUNT,
	.inputLabelIds = BrakeActuator_FR_LDM_R_labelIds,
	.inputData = BrakeActuator_FR_LDM_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable ABS_RL_T configuration
 *************************************************************************/
/**** READ ****/
#define 		ABS_RL_T_READ_COUNT		1
labelId_t 	ABS_RL_T_R_labelIds[ABS_RL_T_READ_COUNT] = {L_ABS_RL_SIG};

uint8_t r_ABS_RL_T_ABS_RL_Sig_buffer[L_ABS_RL_SIG_SIZE];	// Local buffer for label ABS_RL_T
localLabel_t r_ABS_RL_T_ABS_RL_Sig = {
	.data = r_ABS_RL_T_ABS_RL_Sig_buffer,
	.size = L_ABS_RL_SIG_SIZE
};


localLabel_t* ABS_RL_T_R_copies[ABS_RL_T_READ_COUNT] = {
	&r_ABS_RL_T_ABS_RL_Sig,
};

/**** WRITE ****/
#define 		ABS_RL_T_WRITE_COUNT	1
labelId_t 	ABS_RL_T_W_labelIds[ABS_RL_T_WRITE_COUNT] = {L_BRAKE_RL_SIG};

uint8_t w_ABS_RL_T_Brake_RL_Sig_buffer[L_BRAKE_RL_SIG_SIZE];	// Local buffer for label ABS_RL_T
localLabel_t w_ABS_RL_T_Brake_RL_Sig = {
	.data = w_ABS_RL_T_Brake_RL_Sig_buffer,
	.size = L_BRAKE_RL_SIG_SIZE
};

localLabel_t* ABS_RL_T_W_copies[ABS_RL_T_WRITE_COUNT] = {
	&w_ABS_RL_T_Brake_RL_Sig,
};

/**** CONFIGURATION ****/
runnable_spec_t ABS_RL_T = {
	.name = "ABS_RL_T",
	.func = r_ABS_RL_T,
	.init = r_ABS_RL_T_init,
	.deinit = r_ABS_RL_T_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = ABS_RL_T_READ_COUNT,
	.inputLabelIds = ABS_RL_T_R_labelIds,
	.inputData = ABS_RL_T_R_copies,
	.outputLabelCount = ABS_RL_T_WRITE_COUNT,
	.outputLabelIds = ABS_RL_T_W_labelIds,
	.outputData = ABS_RL_T_W_copies
};

/**************************************************************************
 * Runnable BrakeActuator_RL_LDM configuration
 *************************************************************************/
/**** READ ****/
#define 		BRAKEACTUATOR_RL_LDM_READ_COUNT		1
labelId_t 	BrakeActuator_RL_LDM_R_labelIds[BRAKEACTUATOR_RL_LDM_READ_COUNT] = {L_BRAKE_RL_SIG};

uint8_t r_BrakeActuator_RL_LDM_Brake_RL_Sig_buffer[L_BRAKE_RL_SIG_SIZE];	// Local buffer for label BrakeActuator_RL_LDM
localLabel_t r_BrakeActuator_RL_LDM_Brake_RL_Sig = {
	.data = r_BrakeActuator_RL_LDM_Brake_RL_Sig_buffer,
	.size = L_BRAKE_RL_SIG_SIZE
};


localLabel_t* BrakeActuator_RL_LDM_R_copies[BRAKEACTUATOR_RL_LDM_READ_COUNT] = {
	&r_BrakeActuator_RL_LDM_Brake_RL_Sig,
};


/**** CONFIGURATION ****/
runnable_spec_t BrakeActuator_RL_LDM = {
	.name = "BrakeActuator_RL_LDM",
	.func = r_BrakeActuator_RL_LDM,
	.init = r_BrakeActuator_RL_LDM_init,
	.deinit = r_BrakeActuator_RL_LDM_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = BRAKEACTUATOR_RL_LDM_READ_COUNT,
	.inputLabelIds = BrakeActuator_RL_LDM_R_labelIds,
	.inputData = BrakeActuator_RL_LDM_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable ABS_RR_T configuration
 *************************************************************************/
/**** READ ****/
#define 		ABS_RR_T_READ_COUNT		1
labelId_t 	ABS_RR_T_R_labelIds[ABS_RR_T_READ_COUNT] = {L_ABS_RR_SIG};

uint8_t r_ABS_RR_T_ABS_RR_Sig_buffer[L_ABS_RR_SIG_SIZE];	// Local buffer for label ABS_RR_T
localLabel_t r_ABS_RR_T_ABS_RR_Sig = {
	.data = r_ABS_RR_T_ABS_RR_Sig_buffer,
	.size = L_ABS_RR_SIG_SIZE
};


localLabel_t* ABS_RR_T_R_copies[ABS_RR_T_READ_COUNT] = {
	&r_ABS_RR_T_ABS_RR_Sig,
};

/**** WRITE ****/
#define 		ABS_RR_T_WRITE_COUNT	1
labelId_t 	ABS_RR_T_W_labelIds[ABS_RR_T_WRITE_COUNT] = {L_BRAKE_RR_SIG};

uint8_t w_ABS_RR_T_Brake_RR_Sig_buffer[L_BRAKE_RR_SIG_SIZE];	// Local buffer for label ABS_RR_T
localLabel_t w_ABS_RR_T_Brake_RR_Sig = {
	.data = w_ABS_RR_T_Brake_RR_Sig_buffer,
	.size = L_BRAKE_RR_SIG_SIZE
};

localLabel_t* ABS_RR_T_W_copies[ABS_RR_T_WRITE_COUNT] = {
	&w_ABS_RR_T_Brake_RR_Sig,
};

/**** CONFIGURATION ****/
runnable_spec_t ABS_RR_T = {
	.name = "ABS_RR_T",
	.func = r_ABS_RR_T,
	.init = r_ABS_RR_T_init,
	.deinit = r_ABS_RR_T_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = ABS_RR_T_READ_COUNT,
	.inputLabelIds = ABS_RR_T_R_labelIds,
	.inputData = ABS_RR_T_R_copies,
	.outputLabelCount = ABS_RR_T_WRITE_COUNT,
	.outputLabelIds = ABS_RR_T_W_labelIds,
	.outputData = ABS_RR_T_W_copies
};

/**************************************************************************
 * Runnable BrakeActuator_RR_LDM configuration
 *************************************************************************/
/**** READ ****/
#define 		BRAKEACTUATOR_RR_LDM_READ_COUNT		1
labelId_t 	BrakeActuator_RR_LDM_R_labelIds[BRAKEACTUATOR_RR_LDM_READ_COUNT] = {L_BRAKE_RR_SIG};

uint8_t r_BrakeActuator_RR_LDM_Brake_RR_Sig_buffer[L_BRAKE_RR_SIG_SIZE];	// Local buffer for label BrakeActuator_RR_LDM
localLabel_t r_BrakeActuator_RR_LDM_Brake_RR_Sig = {
	.data = r_BrakeActuator_RR_LDM_Brake_RR_Sig_buffer,
	.size = L_BRAKE_RR_SIG_SIZE
};


localLabel_t* BrakeActuator_RR_LDM_R_copies[BRAKEACTUATOR_RR_LDM_READ_COUNT] = {
	&r_BrakeActuator_RR_LDM_Brake_RR_Sig,
};


/**** CONFIGURATION ****/
runnable_spec_t BrakeActuator_RR_LDM = {
	.name = "BrakeActuator_RR_LDM",
	.func = r_BrakeActuator_RR_LDM,
	.init = r_BrakeActuator_RR_LDM_init,
	.deinit = r_BrakeActuator_RR_LDM_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = BRAKEACTUATOR_RR_LDM_READ_COUNT,
	.inputLabelIds = BrakeActuator_RR_LDM_R_labelIds,
	.inputData = BrakeActuator_RR_LDM_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable BrakePedalLDM_T configuration
 *************************************************************************/
/**** WRITE ****/
#define 		BRAKEPEDALLDM_T_WRITE_COUNT	1
labelId_t 	BrakePedalLDM_T_W_labelIds[BRAKEPEDALLDM_T_WRITE_COUNT] = {L_BRAKESIG};

uint8_t w_BrakePedalLDM_T_BrakeSig_buffer[L_BRAKESIG_SIZE];	// Local buffer for label BrakePedalLDM_T
localLabel_t w_BrakePedalLDM_T_BrakeSig = {
	.data = w_BrakePedalLDM_T_BrakeSig_buffer,
	.size = L_BRAKESIG_SIZE
};

localLabel_t* BrakePedalLDM_T_W_copies[BRAKEPEDALLDM_T_WRITE_COUNT] = {
	&w_BrakePedalLDM_T_BrakeSig,
};

/**** CONFIGURATION ****/
runnable_spec_t BrakePedalLDM_T = {
	.name = "BrakePedalLDM_T",
	.func = r_BrakePedalLDM_T,
	.init = r_BrakePedalLDM_T_init,
	.deinit = r_BrakePedalLDM_T_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = BRAKEPEDALLDM_T_WRITE_COUNT,
	.outputLabelIds = BrakePedalLDM_T_W_labelIds,
	.outputData = BrakePedalLDM_T_W_copies
};

/**************************************************************************
 * Runnable BrakeTorqMap configuration
 *************************************************************************/
/**** READ ****/
#define 		BRAKETORQMAP_READ_COUNT		1
labelId_t 	BrakeTorqMap_R_labelIds[BRAKETORQMAP_READ_COUNT] = {L_BRAKESIG};

uint8_t r_BrakeTorqMap_BrakeSig_buffer[L_BRAKESIG_SIZE];	// Local buffer for label BrakeTorqMap
localLabel_t r_BrakeTorqMap_BrakeSig = {
	.data = r_BrakeTorqMap_BrakeSig_buffer,
	.size = L_BRAKESIG_SIZE
};


localLabel_t* BrakeTorqMap_R_copies[BRAKETORQMAP_READ_COUNT] = {
	&r_BrakeTorqMap_BrakeSig,
};

/**** WRITE ****/
#define 		BRAKETORQMAP_WRITE_COUNT	1
labelId_t 	BrakeTorqMap_W_labelIds[BRAKETORQMAP_WRITE_COUNT] = {L_TORQUESIG};

uint8_t w_BrakeTorqMap_TorqueSig_buffer[L_TORQUESIG_SIZE];	// Local buffer for label BrakeTorqMap
localLabel_t w_BrakeTorqMap_TorqueSig = {
	.data = w_BrakeTorqMap_TorqueSig_buffer,
	.size = L_TORQUESIG_SIZE
};

localLabel_t* BrakeTorqMap_W_copies[BRAKETORQMAP_WRITE_COUNT] = {
	&w_BrakeTorqMap_TorqueSig,
};

/**** CONFIGURATION ****/
runnable_spec_t BrakeTorqMap = {
	.name = "BrakeTorqMap",
	.func = r_BrakeTorqMap,
	.init = r_BrakeTorqMap_init,
	.deinit = r_BrakeTorqMap_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = BRAKETORQMAP_READ_COUNT,
	.inputLabelIds = BrakeTorqMap_R_labelIds,
	.inputData = BrakeTorqMap_R_copies,
	.outputLabelCount = BRAKETORQMAP_WRITE_COUNT,
	.outputLabelIds = BrakeTorqMap_W_labelIds,
	.outputData = BrakeTorqMap_W_copies
};

/**************************************************************************
 * Runnable GlobalBrakeController configuration
 *************************************************************************/
/**** READ ****/
#define 		GLOBALBRAKECONTROLLER_READ_COUNT		1
labelId_t 	GlobalBrakeController_R_labelIds[GLOBALBRAKECONTROLLER_READ_COUNT] = {L_TORQUESIG};

uint8_t r_GlobalBrakeController_TorqueSig_buffer[L_TORQUESIG_SIZE];	// Local buffer for label GlobalBrakeController
localLabel_t r_GlobalBrakeController_TorqueSig = {
	.data = r_GlobalBrakeController_TorqueSig_buffer,
	.size = L_TORQUESIG_SIZE
};


localLabel_t* GlobalBrakeController_R_copies[GLOBALBRAKECONTROLLER_READ_COUNT] = {
	&r_GlobalBrakeController_TorqueSig,
};

/**** WRITE ****/
#define 		GLOBALBRAKECONTROLLER_WRITE_COUNT	4
labelId_t 	GlobalBrakeController_W_labelIds[GLOBALBRAKECONTROLLER_WRITE_COUNT] = {L_ABS_FL_SIG, L_ABS_FR_SIG, L_ABS_RL_SIG, L_ABS_RR_SIG};

uint8_t w_GlobalBrakeController_ABS_FL_Sig_buffer[L_ABS_FL_SIG_SIZE];	// Local buffer for label GlobalBrakeController
localLabel_t w_GlobalBrakeController_ABS_FL_Sig = {
	.data = w_GlobalBrakeController_ABS_FL_Sig_buffer,
	.size = L_ABS_FL_SIG_SIZE
};
uint8_t w_GlobalBrakeController_ABS_FR_Sig_buffer[L_ABS_FR_SIG_SIZE];	// Local buffer for label GlobalBrakeController
localLabel_t w_GlobalBrakeController_ABS_FR_Sig = {
	.data = w_GlobalBrakeController_ABS_FR_Sig_buffer,
	.size = L_ABS_FR_SIG_SIZE
};
uint8_t w_GlobalBrakeController_ABS_RL_Sig_buffer[L_ABS_RL_SIG_SIZE];	// Local buffer for label GlobalBrakeController
localLabel_t w_GlobalBrakeController_ABS_RL_Sig = {
	.data = w_GlobalBrakeController_ABS_RL_Sig_buffer,
	.size = L_ABS_RL_SIG_SIZE
};
uint8_t w_GlobalBrakeController_ABS_RR_Sig_buffer[L_ABS_RR_SIG_SIZE];	// Local buffer for label GlobalBrakeController
localLabel_t w_GlobalBrakeController_ABS_RR_Sig = {
	.data = w_GlobalBrakeController_ABS_RR_Sig_buffer,
	.size = L_ABS_RR_SIG_SIZE
};

localLabel_t* GlobalBrakeController_W_copies[GLOBALBRAKECONTROLLER_WRITE_COUNT] = {
	&w_GlobalBrakeController_ABS_FL_Sig,
	&w_GlobalBrakeController_ABS_FR_Sig,
	&w_GlobalBrakeController_ABS_RL_Sig,
	&w_GlobalBrakeController_ABS_RR_Sig,
};

/**** CONFIGURATION ****/
runnable_spec_t GlobalBrakeController = {
	.name = "GlobalBrakeController",
	.func = r_GlobalBrakeController,
	.init = r_GlobalBrakeController_init,
	.deinit = r_GlobalBrakeController_deinit,
	.initialized = false,
	.mode = 1,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = GLOBALBRAKECONTROLLER_READ_COUNT,
	.inputLabelIds = GlobalBrakeController_R_labelIds,
	.inputData = GlobalBrakeController_R_copies,
	.outputLabelCount = GLOBALBRAKECONTROLLER_WRITE_COUNT,
	.outputLabelIds = GlobalBrakeController_W_labelIds,
	.outputData = GlobalBrakeController_W_copies
};

#endif //USER_RUNNABLES_H
