#ifndef USER_RUNNABLES_H
#define USER_RUNNABLES_H

/**
 * Function prototypes for all runnables
 */

/* Functions for Runnable CAN_Func */
void r_CAN_Func_init(runnable_spec_t* spec);
void r_CAN_Func(runnable_spec_t* spec);
void r_CAN_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable EKF_Func */
void r_EKF_Func_init(runnable_spec_t* spec);
void r_EKF_Func(runnable_spec_t* spec);
void r_EKF_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable Tx_EKF_to_RaspberryPi_2 */
void r_Tx_EKF_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Tx_EKF_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Tx_EKF_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/* Functions for Runnable Lidar_Func */
void r_Lidar_Func_init(runnable_spec_t* spec);
void r_Lidar_Func(runnable_spec_t* spec);
void r_Lidar_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable Tx_Lidar_to_RaspberryPi_2 */
void r_Tx_Lidar_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Tx_Lidar_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Tx_Lidar_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/* Functions for Runnable Detection_Func */
void r_Detection_Func_init(runnable_spec_t* spec);
void r_Detection_Func(runnable_spec_t* spec);
void r_Detection_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable Tx_Detection_to_RaspberryPi_2 */
void r_Tx_Detection_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Tx_Detection_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Tx_Detection_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/* Functions for Runnable Localization_Func */
void r_Localization_Func_init(runnable_spec_t* spec);
void r_Localization_Func(runnable_spec_t* spec);
void r_Localization_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable Tx_Localization_to_RaspberryPi_2 */
void r_Tx_Localization_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Tx_Localization_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Tx_Localization_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/**************************************************************************
 * Runnable CAN_Func configuration
 *************************************************************************/
/**** WRITE ****/
#define 		CAN_FUNC_WRITE_COUNT	1
labelId_t 	CAN_Func_W_labelIds[CAN_FUNC_WRITE_COUNT] = {L_VEHICLE_STATUS};

uint8_t w_CAN_Func_vehicle_status_buffer[L_VEHICLE_STATUS_SIZE];	// Local buffer for label CAN_Func
localLabel_t w_CAN_Func_vehicle_status = {
	.data = w_CAN_Func_vehicle_status_buffer,
	.size = L_VEHICLE_STATUS_SIZE
};

localLabel_t* CAN_Func_W_copies[CAN_FUNC_WRITE_COUNT] = {
	&w_CAN_Func_vehicle_status,
};

/**** CONFIGURATION ****/
runnable_spec_t CAN_Func = {
	.name = "CAN_Func",
	.func = r_CAN_Func,
	.init = r_CAN_Func_init,
	.deinit = r_CAN_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = CAN_FUNC_WRITE_COUNT,
	.outputLabelIds = CAN_Func_W_labelIds,
	.outputData = CAN_Func_W_copies
};

/**************************************************************************
 * Runnable EKF_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		EKF_FUNC_READ_COUNT		4
labelId_t 	EKF_Func_R_labelIds[EKF_FUNC_READ_COUNT] = {L_VEHICLE_STATUS, L_X_CAR, L_Y_CAR, L_YAW_CAR};

uint8_t r_EKF_Func_vehicle_status_buffer[L_VEHICLE_STATUS_SIZE];	// Local buffer for label EKF_Func
localLabel_t r_EKF_Func_vehicle_status = {
	.data = r_EKF_Func_vehicle_status_buffer,
	.size = L_VEHICLE_STATUS_SIZE
};

uint8_t r_EKF_Func_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label EKF_Func
localLabel_t r_EKF_Func_x_car = {
	.data = r_EKF_Func_x_car_buffer,
	.size = L_X_CAR_SIZE
};

uint8_t r_EKF_Func_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label EKF_Func
localLabel_t r_EKF_Func_y_car = {
	.data = r_EKF_Func_y_car_buffer,
	.size = L_Y_CAR_SIZE
};

uint8_t r_EKF_Func_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label EKF_Func
localLabel_t r_EKF_Func_yaw_car = {
	.data = r_EKF_Func_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};


localLabel_t* EKF_Func_R_copies[EKF_FUNC_READ_COUNT] = {
	&r_EKF_Func_vehicle_status,
	&r_EKF_Func_x_car,
	&r_EKF_Func_y_car,
	&r_EKF_Func_yaw_car,
};

/**** WRITE ****/
#define 		EKF_FUNC_WRITE_COUNT	5
labelId_t 	EKF_Func_W_labelIds[EKF_FUNC_WRITE_COUNT] = {L_X_CAR, L_Y_CAR, L_YAW_CAR, L_VEL_CAR, L_YAW_RATE};

uint8_t w_EKF_Func_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label EKF_Func
localLabel_t w_EKF_Func_x_car = {
	.data = w_EKF_Func_x_car_buffer,
	.size = L_X_CAR_SIZE
};
uint8_t w_EKF_Func_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label EKF_Func
localLabel_t w_EKF_Func_y_car = {
	.data = w_EKF_Func_y_car_buffer,
	.size = L_Y_CAR_SIZE
};
uint8_t w_EKF_Func_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label EKF_Func
localLabel_t w_EKF_Func_yaw_car = {
	.data = w_EKF_Func_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};
uint8_t w_EKF_Func_vel_car_buffer[L_VEL_CAR_SIZE];	// Local buffer for label EKF_Func
localLabel_t w_EKF_Func_vel_car = {
	.data = w_EKF_Func_vel_car_buffer,
	.size = L_VEL_CAR_SIZE
};
uint8_t w_EKF_Func_yaw_rate_buffer[L_YAW_RATE_SIZE];	// Local buffer for label EKF_Func
localLabel_t w_EKF_Func_yaw_rate = {
	.data = w_EKF_Func_yaw_rate_buffer,
	.size = L_YAW_RATE_SIZE
};

localLabel_t* EKF_Func_W_copies[EKF_FUNC_WRITE_COUNT] = {
	&w_EKF_Func_x_car,
	&w_EKF_Func_y_car,
	&w_EKF_Func_yaw_car,
	&w_EKF_Func_vel_car,
	&w_EKF_Func_yaw_rate,
};

/**** CONFIGURATION ****/
runnable_spec_t EKF_Func = {
	.name = "EKF_Func",
	.func = r_EKF_Func,
	.init = r_EKF_Func_init,
	.deinit = r_EKF_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = EKF_FUNC_READ_COUNT,
	.inputLabelIds = EKF_Func_R_labelIds,
	.inputData = EKF_Func_R_copies,
	.outputLabelCount = EKF_FUNC_WRITE_COUNT,
	.outputLabelIds = EKF_Func_W_labelIds,
	.outputData = EKF_Func_W_copies
};

/**************************************************************************
 * Runnable Tx_EKF_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** READ ****/
#define 		TX_EKF_TO_RASPBERRYPI_2_READ_COUNT		5
labelId_t 	Tx_EKF_to_RaspberryPi_2_R_labelIds[TX_EKF_TO_RASPBERRYPI_2_READ_COUNT] = {L_X_CAR, L_Y_CAR, L_YAW_CAR, L_VEL_CAR, L_YAW_RATE};

uint8_t r_Tx_EKF_to_RaspberryPi_2_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label Tx_EKF_to_RaspberryPi_2
localLabel_t r_Tx_EKF_to_RaspberryPi_2_x_car = {
	.data = r_Tx_EKF_to_RaspberryPi_2_x_car_buffer,
	.size = L_X_CAR_SIZE
};

uint8_t r_Tx_EKF_to_RaspberryPi_2_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label Tx_EKF_to_RaspberryPi_2
localLabel_t r_Tx_EKF_to_RaspberryPi_2_y_car = {
	.data = r_Tx_EKF_to_RaspberryPi_2_y_car_buffer,
	.size = L_Y_CAR_SIZE
};

uint8_t r_Tx_EKF_to_RaspberryPi_2_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label Tx_EKF_to_RaspberryPi_2
localLabel_t r_Tx_EKF_to_RaspberryPi_2_yaw_car = {
	.data = r_Tx_EKF_to_RaspberryPi_2_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};

uint8_t r_Tx_EKF_to_RaspberryPi_2_vel_car_buffer[L_VEL_CAR_SIZE];	// Local buffer for label Tx_EKF_to_RaspberryPi_2
localLabel_t r_Tx_EKF_to_RaspberryPi_2_vel_car = {
	.data = r_Tx_EKF_to_RaspberryPi_2_vel_car_buffer,
	.size = L_VEL_CAR_SIZE
};

uint8_t r_Tx_EKF_to_RaspberryPi_2_yaw_rate_buffer[L_YAW_RATE_SIZE];	// Local buffer for label Tx_EKF_to_RaspberryPi_2
localLabel_t r_Tx_EKF_to_RaspberryPi_2_yaw_rate = {
	.data = r_Tx_EKF_to_RaspberryPi_2_yaw_rate_buffer,
	.size = L_YAW_RATE_SIZE
};


localLabel_t* Tx_EKF_to_RaspberryPi_2_R_copies[TX_EKF_TO_RASPBERRYPI_2_READ_COUNT] = {
	&r_Tx_EKF_to_RaspberryPi_2_x_car,
	&r_Tx_EKF_to_RaspberryPi_2_y_car,
	&r_Tx_EKF_to_RaspberryPi_2_yaw_car,
	&r_Tx_EKF_to_RaspberryPi_2_vel_car,
	&r_Tx_EKF_to_RaspberryPi_2_yaw_rate,
};


/**** CONFIGURATION ****/
runnable_spec_t Tx_EKF_to_RaspberryPi_2 = {
	.name = "Tx_EKF_to_RaspberryPi_2",
	.func = r_Tx_EKF_to_RaspberryPi_2,
	.init = r_Tx_EKF_to_RaspberryPi_2_init,
	.deinit = r_Tx_EKF_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = TX_EKF_TO_RASPBERRYPI_2_READ_COUNT,
	.inputLabelIds = Tx_EKF_to_RaspberryPi_2_R_labelIds,
	.inputData = Tx_EKF_to_RaspberryPi_2_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable Lidar_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		LIDAR_FUNC_READ_COUNT		1
labelId_t 	Lidar_Func_R_labelIds[LIDAR_FUNC_READ_COUNT] = {L_CLOUD_MAP};

uint8_t r_Lidar_Func_cloud_map_buffer[L_CLOUD_MAP_SIZE];	// Local buffer for label Lidar_Func
localLabel_t r_Lidar_Func_cloud_map = {
	.data = r_Lidar_Func_cloud_map_buffer,
	.size = L_CLOUD_MAP_SIZE
};


localLabel_t* Lidar_Func_R_copies[LIDAR_FUNC_READ_COUNT] = {
	&r_Lidar_Func_cloud_map,
};

/**** WRITE ****/
#define 		LIDAR_FUNC_WRITE_COUNT	2
labelId_t 	Lidar_Func_W_labelIds[LIDAR_FUNC_WRITE_COUNT] = {L_CLOUD_MAP, L_OCCUPANCY_GRID};

uint8_t w_Lidar_Func_cloud_map_buffer[L_CLOUD_MAP_SIZE];	// Local buffer for label Lidar_Func
localLabel_t w_Lidar_Func_cloud_map = {
	.data = w_Lidar_Func_cloud_map_buffer,
	.size = L_CLOUD_MAP_SIZE
};
uint8_t w_Lidar_Func_occupancy_grid_buffer[L_OCCUPANCY_GRID_SIZE];	// Local buffer for label Lidar_Func
localLabel_t w_Lidar_Func_occupancy_grid = {
	.data = w_Lidar_Func_occupancy_grid_buffer,
	.size = L_OCCUPANCY_GRID_SIZE
};

localLabel_t* Lidar_Func_W_copies[LIDAR_FUNC_WRITE_COUNT] = {
	&w_Lidar_Func_cloud_map,
	&w_Lidar_Func_occupancy_grid,
};

/**** CONFIGURATION ****/
runnable_spec_t Lidar_Func = {
	.name = "Lidar_Func",
	.func = r_Lidar_Func,
	.init = r_Lidar_Func_init,
	.deinit = r_Lidar_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = LIDAR_FUNC_READ_COUNT,
	.inputLabelIds = Lidar_Func_R_labelIds,
	.inputData = Lidar_Func_R_copies,
	.outputLabelCount = LIDAR_FUNC_WRITE_COUNT,
	.outputLabelIds = Lidar_Func_W_labelIds,
	.outputData = Lidar_Func_W_copies
};

/**************************************************************************
 * Runnable Tx_Lidar_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** READ ****/
#define 		TX_LIDAR_TO_RASPBERRYPI_2_READ_COUNT		1
labelId_t 	Tx_Lidar_to_RaspberryPi_2_R_labelIds[TX_LIDAR_TO_RASPBERRYPI_2_READ_COUNT] = {L_OCCUPANCY_GRID};

uint8_t r_Tx_Lidar_to_RaspberryPi_2_occupancy_grid_buffer[L_OCCUPANCY_GRID_SIZE];	// Local buffer for label Tx_Lidar_to_RaspberryPi_2
localLabel_t r_Tx_Lidar_to_RaspberryPi_2_occupancy_grid = {
	.data = r_Tx_Lidar_to_RaspberryPi_2_occupancy_grid_buffer,
	.size = L_OCCUPANCY_GRID_SIZE
};


localLabel_t* Tx_Lidar_to_RaspberryPi_2_R_copies[TX_LIDAR_TO_RASPBERRYPI_2_READ_COUNT] = {
	&r_Tx_Lidar_to_RaspberryPi_2_occupancy_grid,
};


/**** CONFIGURATION ****/
runnable_spec_t Tx_Lidar_to_RaspberryPi_2 = {
	.name = "Tx_Lidar_to_RaspberryPi_2",
	.func = r_Tx_Lidar_to_RaspberryPi_2,
	.init = r_Tx_Lidar_to_RaspberryPi_2_init,
	.deinit = r_Tx_Lidar_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = TX_LIDAR_TO_RASPBERRYPI_2_READ_COUNT,
	.inputLabelIds = Tx_Lidar_to_RaspberryPi_2_R_labelIds,
	.inputData = Tx_Lidar_to_RaspberryPi_2_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable Detection_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		DETECTION_FUNC_READ_COUNT		1
labelId_t 	Detection_Func_R_labelIds[DETECTION_FUNC_READ_COUNT] = {L_IMAGE_LANE};

uint8_t r_Detection_Func_image_lane_buffer[L_IMAGE_LANE_SIZE];	// Local buffer for label Detection_Func
localLabel_t r_Detection_Func_image_lane = {
	.data = r_Detection_Func_image_lane_buffer,
	.size = L_IMAGE_LANE_SIZE
};


localLabel_t* Detection_Func_R_copies[DETECTION_FUNC_READ_COUNT] = {
	&r_Detection_Func_image_lane,
};

/**** WRITE ****/
#define 		DETECTION_FUNC_WRITE_COUNT	1
labelId_t 	Detection_Func_W_labelIds[DETECTION_FUNC_WRITE_COUNT] = {L_BOUNDARY_BOX};

uint8_t w_Detection_Func_boundary_box_buffer[L_BOUNDARY_BOX_SIZE];	// Local buffer for label Detection_Func
localLabel_t w_Detection_Func_boundary_box = {
	.data = w_Detection_Func_boundary_box_buffer,
	.size = L_BOUNDARY_BOX_SIZE
};

localLabel_t* Detection_Func_W_copies[DETECTION_FUNC_WRITE_COUNT] = {
	&w_Detection_Func_boundary_box,
};

/**** CONFIGURATION ****/
runnable_spec_t Detection_Func = {
	.name = "Detection_Func",
	.func = r_Detection_Func,
	.init = r_Detection_Func_init,
	.deinit = r_Detection_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = DETECTION_FUNC_READ_COUNT,
	.inputLabelIds = Detection_Func_R_labelIds,
	.inputData = Detection_Func_R_copies,
	.outputLabelCount = DETECTION_FUNC_WRITE_COUNT,
	.outputLabelIds = Detection_Func_W_labelIds,
	.outputData = Detection_Func_W_copies
};

/**************************************************************************
 * Runnable Tx_Detection_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** READ ****/
#define 		TX_DETECTION_TO_RASPBERRYPI_2_READ_COUNT		1
labelId_t 	Tx_Detection_to_RaspberryPi_2_R_labelIds[TX_DETECTION_TO_RASPBERRYPI_2_READ_COUNT] = {L_BOUNDARY_BOX};

uint8_t r_Tx_Detection_to_RaspberryPi_2_boundary_box_buffer[L_BOUNDARY_BOX_SIZE];	// Local buffer for label Tx_Detection_to_RaspberryPi_2
localLabel_t r_Tx_Detection_to_RaspberryPi_2_boundary_box = {
	.data = r_Tx_Detection_to_RaspberryPi_2_boundary_box_buffer,
	.size = L_BOUNDARY_BOX_SIZE
};


localLabel_t* Tx_Detection_to_RaspberryPi_2_R_copies[TX_DETECTION_TO_RASPBERRYPI_2_READ_COUNT] = {
	&r_Tx_Detection_to_RaspberryPi_2_boundary_box,
};


/**** CONFIGURATION ****/
runnable_spec_t Tx_Detection_to_RaspberryPi_2 = {
	.name = "Tx_Detection_to_RaspberryPi_2",
	.func = r_Tx_Detection_to_RaspberryPi_2,
	.init = r_Tx_Detection_to_RaspberryPi_2_init,
	.deinit = r_Tx_Detection_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = TX_DETECTION_TO_RASPBERRYPI_2_READ_COUNT,
	.inputLabelIds = Tx_Detection_to_RaspberryPi_2_R_labelIds,
	.inputData = Tx_Detection_to_RaspberryPi_2_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

/**************************************************************************
 * Runnable Localization_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		LOCALIZATION_FUNC_READ_COUNT		2
labelId_t 	Localization_Func_R_labelIds[LOCALIZATION_FUNC_READ_COUNT] = {L_CLOUD_MAP, L_VEHICLE_STATUS};

uint8_t r_Localization_Func_cloud_map_buffer[L_CLOUD_MAP_SIZE];	// Local buffer for label Localization_Func
localLabel_t r_Localization_Func_cloud_map = {
	.data = r_Localization_Func_cloud_map_buffer,
	.size = L_CLOUD_MAP_SIZE
};

uint8_t r_Localization_Func_vehicle_status_buffer[L_VEHICLE_STATUS_SIZE];	// Local buffer for label Localization_Func
localLabel_t r_Localization_Func_vehicle_status = {
	.data = r_Localization_Func_vehicle_status_buffer,
	.size = L_VEHICLE_STATUS_SIZE
};


localLabel_t* Localization_Func_R_copies[LOCALIZATION_FUNC_READ_COUNT] = {
	&r_Localization_Func_cloud_map,
	&r_Localization_Func_vehicle_status,
};

/**** WRITE ****/
#define 		LOCALIZATION_FUNC_WRITE_COUNT	3
labelId_t 	Localization_Func_W_labelIds[LOCALIZATION_FUNC_WRITE_COUNT] = {L_X_CAR, L_Y_CAR, L_YAW_CAR};

uint8_t w_Localization_Func_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label Localization_Func
localLabel_t w_Localization_Func_x_car = {
	.data = w_Localization_Func_x_car_buffer,
	.size = L_X_CAR_SIZE
};
uint8_t w_Localization_Func_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label Localization_Func
localLabel_t w_Localization_Func_y_car = {
	.data = w_Localization_Func_y_car_buffer,
	.size = L_Y_CAR_SIZE
};
uint8_t w_Localization_Func_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label Localization_Func
localLabel_t w_Localization_Func_yaw_car = {
	.data = w_Localization_Func_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};

localLabel_t* Localization_Func_W_copies[LOCALIZATION_FUNC_WRITE_COUNT] = {
	&w_Localization_Func_x_car,
	&w_Localization_Func_y_car,
	&w_Localization_Func_yaw_car,
};

/**** CONFIGURATION ****/
runnable_spec_t Localization_Func = {
	.name = "Localization_Func",
	.func = r_Localization_Func,
	.init = r_Localization_Func_init,
	.deinit = r_Localization_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = LOCALIZATION_FUNC_READ_COUNT,
	.inputLabelIds = Localization_Func_R_labelIds,
	.inputData = Localization_Func_R_copies,
	.outputLabelCount = LOCALIZATION_FUNC_WRITE_COUNT,
	.outputLabelIds = Localization_Func_W_labelIds,
	.outputData = Localization_Func_W_copies
};

/**************************************************************************
 * Runnable Tx_Localization_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** READ ****/
#define 		TX_LOCALIZATION_TO_RASPBERRYPI_2_READ_COUNT		3
labelId_t 	Tx_Localization_to_RaspberryPi_2_R_labelIds[TX_LOCALIZATION_TO_RASPBERRYPI_2_READ_COUNT] = {L_X_CAR, L_Y_CAR, L_YAW_CAR};

uint8_t r_Tx_Localization_to_RaspberryPi_2_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label Tx_Localization_to_RaspberryPi_2
localLabel_t r_Tx_Localization_to_RaspberryPi_2_x_car = {
	.data = r_Tx_Localization_to_RaspberryPi_2_x_car_buffer,
	.size = L_X_CAR_SIZE
};

uint8_t r_Tx_Localization_to_RaspberryPi_2_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label Tx_Localization_to_RaspberryPi_2
localLabel_t r_Tx_Localization_to_RaspberryPi_2_y_car = {
	.data = r_Tx_Localization_to_RaspberryPi_2_y_car_buffer,
	.size = L_Y_CAR_SIZE
};

uint8_t r_Tx_Localization_to_RaspberryPi_2_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label Tx_Localization_to_RaspberryPi_2
localLabel_t r_Tx_Localization_to_RaspberryPi_2_yaw_car = {
	.data = r_Tx_Localization_to_RaspberryPi_2_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};


localLabel_t* Tx_Localization_to_RaspberryPi_2_R_copies[TX_LOCALIZATION_TO_RASPBERRYPI_2_READ_COUNT] = {
	&r_Tx_Localization_to_RaspberryPi_2_x_car,
	&r_Tx_Localization_to_RaspberryPi_2_y_car,
	&r_Tx_Localization_to_RaspberryPi_2_yaw_car,
};


/**** CONFIGURATION ****/
runnable_spec_t Tx_Localization_to_RaspberryPi_2 = {
	.name = "Tx_Localization_to_RaspberryPi_2",
	.func = r_Tx_Localization_to_RaspberryPi_2,
	.init = r_Tx_Localization_to_RaspberryPi_2_init,
	.deinit = r_Tx_Localization_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = TX_LOCALIZATION_TO_RASPBERRYPI_2_READ_COUNT,
	.inputLabelIds = Tx_Localization_to_RaspberryPi_2_R_labelIds,
	.inputData = Tx_Localization_to_RaspberryPi_2_R_copies,
	.outputLabelCount = 0,
	.outputLabelIds = NULL,
	.outputData = NULL
};

#endif //USER_RUNNABLES_H
