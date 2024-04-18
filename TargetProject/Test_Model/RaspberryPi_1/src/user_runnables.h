#ifndef USER_RUNNABLES_H
#define USER_RUNNABLES_H

/**
 * Function prototypes for all runnables
 */

/* Functions for Runnable A */
void r_A_init(runnable_spec_t* spec);
void r_A(runnable_spec_t* spec);
void r_A_deinit(runnable_spec_t* spec);

/* Functions for Runnable Tx_A_to_RaspberryPi_2 */
void r_Tx_A_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Tx_A_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Tx_A_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/**************************************************************************
 * Runnable A configuration
 *************************************************************************/
/**** WRITE ****/
#define 		A_WRITE_COUNT	2
labelId_t 	A_W_labelIds[A_WRITE_COUNT] = {L_TMPLABEL, L_TMPLABEL2};

uint8_t w_A_tmpLabel_buffer[L_TMPLABEL_SIZE];	// Local buffer for label A
localLabel_t w_A_tmpLabel = {
	.data = w_A_tmpLabel_buffer,
	.size = L_TMPLABEL_SIZE
};
uint8_t w_A_tmpLabel2_buffer[L_TMPLABEL2_SIZE];	// Local buffer for label A
localLabel_t w_A_tmpLabel2 = {
	.data = w_A_tmpLabel2_buffer,
	.size = L_TMPLABEL2_SIZE
};

localLabel_t* A_W_copies[A_WRITE_COUNT] = {
	&w_A_tmpLabel,
	&w_A_tmpLabel2,
};

/**** CONFIGURATION ****/
runnable_spec_t A = {
	.name = "A",
	.func = r_A,
	.init = r_A_init,
	.deinit = r_A_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = A_WRITE_COUNT,
	.outputLabelIds = A_W_labelIds,
	.outputData = A_W_copies
};

/**************************************************************************
 * Runnable Tx_A_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** READ ****/
#define 		TX_A_TO_RASPBERRYPI_2_READ_COUNT		2
labelId_t 	Tx_A_to_RaspberryPi_2_R_labelIds[TX_A_TO_RASPBERRYPI_2_READ_COUNT] = {L_TMPLABEL, L_TMPLABEL2};

uint8_t r_Tx_A_to_RaspberryPi_2_tmpLabel_buffer[L_TMPLABEL_SIZE];	// Local buffer for label Tx_A_to_RaspberryPi_2
localLabel_t r_Tx_A_to_RaspberryPi_2_tmpLabel = {
	.data = r_Tx_A_to_RaspberryPi_2_tmpLabel_buffer,
	.size = L_TMPLABEL_SIZE
};

uint8_t r_Tx_A_to_RaspberryPi_2_tmpLabel2_buffer[L_TMPLABEL2_SIZE];	// Local buffer for label Tx_A_to_RaspberryPi_2
localLabel_t r_Tx_A_to_RaspberryPi_2_tmpLabel2 = {
	.data = r_Tx_A_to_RaspberryPi_2_tmpLabel2_buffer,
	.size = L_TMPLABEL2_SIZE
};


localLabel_t* Tx_A_to_RaspberryPi_2_R_copies[TX_A_TO_RASPBERRYPI_2_READ_COUNT] = {
	&r_Tx_A_to_RaspberryPi_2_tmpLabel,
	&r_Tx_A_to_RaspberryPi_2_tmpLabel2,
};


/**** CONFIGURATION ****/
runnable_spec_t Tx_A_to_RaspberryPi_2 = {
	.name = "Tx_A_to_RaspberryPi_2",
	.func = r_Tx_A_to_RaspberryPi_2,
	.init = r_Tx_A_to_RaspberryPi_2_init,
	.deinit = r_Tx_A_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = TX_A_TO_RASPBERRYPI_2_READ_COUNT,
	.inputLabelIds = Tx_A_to_RaspberryPi_2_R_labelIds,
	.inputData = Tx_A_to_RaspberryPi_2_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

#endif //USER_RUNNABLES_H
