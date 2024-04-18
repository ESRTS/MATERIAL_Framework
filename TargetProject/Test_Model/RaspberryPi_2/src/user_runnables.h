#ifndef USER_RUNNABLES_H
#define USER_RUNNABLES_H

/**
 * Function prototypes for all runnables
 */

/* Functions for Runnable B */
void r_B_init(runnable_spec_t* spec);
void r_B(runnable_spec_t* spec);
void r_B_deinit(runnable_spec_t* spec);

/* Functions for Runnable Rx_A_to_RaspberryPi_2 */
void r_Rx_A_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Rx_A_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Rx_A_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/**************************************************************************
 * Runnable B configuration
 *************************************************************************/
/**** READ ****/
#define 		B_READ_COUNT		2
labelId_t 	B_R_labelIds[B_READ_COUNT] = {L_TMPLABEL2, L_TMPLABEL};

uint8_t r_B_tmpLabel2_buffer[L_TMPLABEL2_SIZE];	// Local buffer for label B
localLabel_t r_B_tmpLabel2 = {
	.data = r_B_tmpLabel2_buffer,
	.size = L_TMPLABEL2_SIZE
};

uint8_t r_B_tmpLabel_buffer[L_TMPLABEL_SIZE];	// Local buffer for label B
localLabel_t r_B_tmpLabel = {
	.data = r_B_tmpLabel_buffer,
	.size = L_TMPLABEL_SIZE
};


localLabel_t* B_R_copies[B_READ_COUNT] = {
	&r_B_tmpLabel2,
	&r_B_tmpLabel,
};


/**** CONFIGURATION ****/
runnable_spec_t B = {
	.name = "B",
	.func = r_B,
	.init = r_B_init,
	.deinit = r_B_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = B_READ_COUNT,
	.inputLabelIds = B_R_labelIds,
	.inputData = B_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable Rx_A_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** WRITE ****/
#define 		RX_A_TO_RASPBERRYPI_2_WRITE_COUNT	2
labelId_t 	Rx_A_to_RaspberryPi_2_W_labelIds[RX_A_TO_RASPBERRYPI_2_WRITE_COUNT] = {L_TMPLABEL, L_TMPLABEL2};

uint8_t w_Rx_A_to_RaspberryPi_2_tmpLabel_buffer[L_TMPLABEL_SIZE];	// Local buffer for label Rx_A_to_RaspberryPi_2
localLabel_t w_Rx_A_to_RaspberryPi_2_tmpLabel = {
	.data = w_Rx_A_to_RaspberryPi_2_tmpLabel_buffer,
	.size = L_TMPLABEL_SIZE
};
uint8_t w_Rx_A_to_RaspberryPi_2_tmpLabel2_buffer[L_TMPLABEL2_SIZE];	// Local buffer for label Rx_A_to_RaspberryPi_2
localLabel_t w_Rx_A_to_RaspberryPi_2_tmpLabel2 = {
	.data = w_Rx_A_to_RaspberryPi_2_tmpLabel2_buffer,
	.size = L_TMPLABEL2_SIZE
};

localLabel_t* Rx_A_to_RaspberryPi_2_W_copies[RX_A_TO_RASPBERRYPI_2_WRITE_COUNT] = {
	&w_Rx_A_to_RaspberryPi_2_tmpLabel,
	&w_Rx_A_to_RaspberryPi_2_tmpLabel2,
};

/**** CONFIGURATION ****/
runnable_spec_t Rx_A_to_RaspberryPi_2 = {
	.name = "Rx_A_to_RaspberryPi_2",
	.func = r_Rx_A_to_RaspberryPi_2,
	.init = r_Rx_A_to_RaspberryPi_2_init,
	.deinit = r_Rx_A_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = RX_A_TO_RASPBERRYPI_2_WRITE_COUNT,
	.outputLabelIds = Rx_A_to_RaspberryPi_2_W_labelIds,
	.outputData = Rx_A_to_RaspberryPi_2_W_copies
};

#endif //USER_RUNNABLES_H
