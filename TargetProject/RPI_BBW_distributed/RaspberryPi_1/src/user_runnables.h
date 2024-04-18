#ifndef USER_RUNNABLES_H
#define USER_RUNNABLES_H

/**
 * Function prototypes for all runnables
 */

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

/* Functions for Runnable Tx_pGlobalBrakeController_to_RaspberryPi_2 */
void r_Tx_pGlobalBrakeController_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Tx_pGlobalBrakeController_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Tx_pGlobalBrakeController_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

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

/**************************************************************************
 * Runnable Tx_pGlobalBrakeController_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** READ ****/
#define 		TX_PGLOBALBRAKECONTROLLER_TO_RASPBERRYPI_2_READ_COUNT		4
labelId_t 	Tx_pGlobalBrakeController_to_RaspberryPi_2_R_labelIds[TX_PGLOBALBRAKECONTROLLER_TO_RASPBERRYPI_2_READ_COUNT] = {L_ABS_FL_SIG, L_ABS_FR_SIG, L_ABS_RL_SIG, L_ABS_RR_SIG};

uint8_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FL_Sig_buffer[L_ABS_FL_SIG_SIZE];	// Local buffer for label Tx_pGlobalBrakeController_to_RaspberryPi_2
localLabel_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FL_Sig = {
	.data = r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FL_Sig_buffer,
	.size = L_ABS_FL_SIG_SIZE
};

uint8_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FR_Sig_buffer[L_ABS_FR_SIG_SIZE];	// Local buffer for label Tx_pGlobalBrakeController_to_RaspberryPi_2
localLabel_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FR_Sig = {
	.data = r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FR_Sig_buffer,
	.size = L_ABS_FR_SIG_SIZE
};

uint8_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RL_Sig_buffer[L_ABS_RL_SIG_SIZE];	// Local buffer for label Tx_pGlobalBrakeController_to_RaspberryPi_2
localLabel_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RL_Sig = {
	.data = r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RL_Sig_buffer,
	.size = L_ABS_RL_SIG_SIZE
};

uint8_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RR_Sig_buffer[L_ABS_RR_SIG_SIZE];	// Local buffer for label Tx_pGlobalBrakeController_to_RaspberryPi_2
localLabel_t r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RR_Sig = {
	.data = r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RR_Sig_buffer,
	.size = L_ABS_RR_SIG_SIZE
};


localLabel_t* Tx_pGlobalBrakeController_to_RaspberryPi_2_R_copies[TX_PGLOBALBRAKECONTROLLER_TO_RASPBERRYPI_2_READ_COUNT] = {
	&r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FL_Sig,
	&r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_FR_Sig,
	&r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RL_Sig,
	&r_Tx_pGlobalBrakeController_to_RaspberryPi_2_ABS_RR_Sig,
};


/**** CONFIGURATION ****/
runnable_spec_t Tx_pGlobalBrakeController_to_RaspberryPi_2 = {
	.name = "Tx_pGlobalBrakeController_to_RaspberryPi_2",
	.func = r_Tx_pGlobalBrakeController_to_RaspberryPi_2,
	.init = r_Tx_pGlobalBrakeController_to_RaspberryPi_2_init,
	.deinit = r_Tx_pGlobalBrakeController_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = TX_PGLOBALBRAKECONTROLLER_TO_RASPBERRYPI_2_READ_COUNT,
	.inputLabelIds = Tx_pGlobalBrakeController_to_RaspberryPi_2_R_labelIds,
	.inputData = Tx_pGlobalBrakeController_to_RaspberryPi_2_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

#endif //USER_RUNNABLES_H
