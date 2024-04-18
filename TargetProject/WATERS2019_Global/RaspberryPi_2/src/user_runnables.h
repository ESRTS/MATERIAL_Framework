#ifndef USER_RUNNABLES_H
#define USER_RUNNABLES_H

/**
 * Function prototypes for all runnables
 */

/* Functions for Runnable Control_Func */
void r_Control_Func_init(runnable_spec_t* spec);
void r_Control_Func(runnable_spec_t* spec);
void r_Control_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable Lane_Detection_Func */
void r_Lane_Detection_Func_init(runnable_spec_t* spec);
void r_Lane_Detection_Func(runnable_spec_t* spec);
void r_Lane_Detection_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable SFM_Func */
void r_SFM_Func_init(runnable_spec_t* spec);
void r_SFM_Func(runnable_spec_t* spec);
void r_SFM_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable Planner_Func */
void r_Planner_Func_init(runnable_spec_t* spec);
void r_Planner_Func(runnable_spec_t* spec);
void r_Planner_Func_deinit(runnable_spec_t* spec);

/* Functions for Runnable Rx_Lidar_to_RaspberryPi_2 */
void r_Rx_Lidar_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Rx_Lidar_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Rx_Lidar_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/* Functions for Runnable Rx_EKF_to_RaspberryPi_2 */
void r_Rx_EKF_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Rx_EKF_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Rx_EKF_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/* Functions for Runnable Rx_Detection_to_RaspberryPi_2 */
void r_Rx_Detection_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Rx_Detection_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Rx_Detection_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/* Functions for Runnable Rx_Localization_to_RaspberryPi_2 */
void r_Rx_Localization_to_RaspberryPi_2_init(runnable_spec_t* spec);
void r_Rx_Localization_to_RaspberryPi_2(runnable_spec_t* spec);
void r_Rx_Localization_to_RaspberryPi_2_deinit(runnable_spec_t* spec);

/**************************************************************************
 * Runnable Control_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		CONTROL_FUNC_READ_COUNT		1
labelId_t 	Control_Func_R_labelIds[CONTROL_FUNC_READ_COUNT] = {L_STEER_OBJECTIVE};

uint8_t r_Control_Func_steer_objective_buffer[L_STEER_OBJECTIVE_SIZE];	// Local buffer for label Control_Func
localLabel_t r_Control_Func_steer_objective = {
	.data = r_Control_Func_steer_objective_buffer,
	.size = L_STEER_OBJECTIVE_SIZE
};


localLabel_t* Control_Func_R_copies[CONTROL_FUNC_READ_COUNT] = {
	&r_Control_Func_steer_objective,
};

/**** WRITE ****/
#define 		CONTROL_FUNC_WRITE_COUNT	2
labelId_t 	Control_Func_W_labelIds[CONTROL_FUNC_WRITE_COUNT] = {L_SPEED_OBJECTIVE, L_STEER_OBJECTIVE};

uint8_t w_Control_Func_speed_objective_buffer[L_SPEED_OBJECTIVE_SIZE];	// Local buffer for label Control_Func
localLabel_t w_Control_Func_speed_objective = {
	.data = w_Control_Func_speed_objective_buffer,
	.size = L_SPEED_OBJECTIVE_SIZE
};
uint8_t w_Control_Func_steer_objective_buffer[L_STEER_OBJECTIVE_SIZE];	// Local buffer for label Control_Func
localLabel_t w_Control_Func_steer_objective = {
	.data = w_Control_Func_steer_objective_buffer,
	.size = L_STEER_OBJECTIVE_SIZE
};

localLabel_t* Control_Func_W_copies[CONTROL_FUNC_WRITE_COUNT] = {
	&w_Control_Func_speed_objective,
	&w_Control_Func_steer_objective,
};

/**** CONFIGURATION ****/
runnable_spec_t Control_Func = {
	.name = "Control_Func",
	.func = r_Control_Func,
	.init = r_Control_Func_init,
	.deinit = r_Control_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = CONTROL_FUNC_READ_COUNT,
	.inputLabelIds = Control_Func_R_labelIds,
	.inputData = Control_Func_R_copies,
	.outputLabelCount = CONTROL_FUNC_WRITE_COUNT,
	.outputLabelIds = Control_Func_W_labelIds,
	.outputData = Control_Func_W_copies
};

/**************************************************************************
 * Runnable Lane_Detection_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		LANE_DETECTION_FUNC_READ_COUNT		1
labelId_t 	Lane_Detection_Func_R_labelIds[LANE_DETECTION_FUNC_READ_COUNT] = {L_IMAGE_LANE};

uint8_t r_Lane_Detection_Func_image_lane_buffer[L_IMAGE_LANE_SIZE];	// Local buffer for label Lane_Detection_Func
localLabel_t r_Lane_Detection_Func_image_lane = {
	.data = r_Lane_Detection_Func_image_lane_buffer,
	.size = L_IMAGE_LANE_SIZE
};


localLabel_t* Lane_Detection_Func_R_copies[LANE_DETECTION_FUNC_READ_COUNT] = {
	&r_Lane_Detection_Func_image_lane,
};

/**** WRITE ****/
#define 		LANE_DETECTION_FUNC_WRITE_COUNT	1
labelId_t 	Lane_Detection_Func_W_labelIds[LANE_DETECTION_FUNC_WRITE_COUNT] = {L_LANE_BOUNDARY};

uint8_t w_Lane_Detection_Func_lane_boundary_buffer[L_LANE_BOUNDARY_SIZE];	// Local buffer for label Lane_Detection_Func
localLabel_t w_Lane_Detection_Func_lane_boundary = {
	.data = w_Lane_Detection_Func_lane_boundary_buffer,
	.size = L_LANE_BOUNDARY_SIZE
};

localLabel_t* Lane_Detection_Func_W_copies[LANE_DETECTION_FUNC_WRITE_COUNT] = {
	&w_Lane_Detection_Func_lane_boundary,
};

/**** CONFIGURATION ****/
runnable_spec_t Lane_Detection_Func = {
	.name = "Lane_Detection_Func",
	.func = r_Lane_Detection_Func,
	.init = r_Lane_Detection_Func_init,
	.deinit = r_Lane_Detection_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = LANE_DETECTION_FUNC_READ_COUNT,
	.inputLabelIds = Lane_Detection_Func_R_labelIds,
	.inputData = Lane_Detection_Func_R_copies,
	.outputLabelCount = LANE_DETECTION_FUNC_WRITE_COUNT,
	.outputLabelIds = Lane_Detection_Func_W_labelIds,
	.outputData = Lane_Detection_Func_W_copies
};

/**************************************************************************
 * Runnable SFM_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		SFM_FUNC_READ_COUNT		1
labelId_t 	SFM_Func_R_labelIds[SFM_FUNC_READ_COUNT] = {L_IMAGE_SFM};

uint8_t r_SFM_Func_image_sfm_buffer[L_IMAGE_SFM_SIZE];	// Local buffer for label SFM_Func
localLabel_t r_SFM_Func_image_sfm = {
	.data = r_SFM_Func_image_sfm_buffer,
	.size = L_IMAGE_SFM_SIZE
};


localLabel_t* SFM_Func_R_copies[SFM_FUNC_READ_COUNT] = {
	&r_SFM_Func_image_sfm,
};

/**** WRITE ****/
#define 		SFM_FUNC_WRITE_COUNT	1
labelId_t 	SFM_Func_W_labelIds[SFM_FUNC_WRITE_COUNT] = {L_MATRIX_SFM};

uint8_t w_SFM_Func_matrix_sfm_buffer[L_MATRIX_SFM_SIZE];	// Local buffer for label SFM_Func
localLabel_t w_SFM_Func_matrix_sfm = {
	.data = w_SFM_Func_matrix_sfm_buffer,
	.size = L_MATRIX_SFM_SIZE
};

localLabel_t* SFM_Func_W_copies[SFM_FUNC_WRITE_COUNT] = {
	&w_SFM_Func_matrix_sfm,
};

/**** CONFIGURATION ****/
runnable_spec_t SFM_Func = {
	.name = "SFM_Func",
	.func = r_SFM_Func,
	.init = r_SFM_Func_init,
	.deinit = r_SFM_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = SFM_FUNC_READ_COUNT,
	.inputLabelIds = SFM_Func_R_labelIds,
	.inputData = SFM_Func_R_copies,
	.outputLabelCount = SFM_FUNC_WRITE_COUNT,
	.outputLabelIds = SFM_Func_W_labelIds,
	.outputData = SFM_Func_W_copies
};

/**************************************************************************
 * Runnable Planner_Func configuration
 *************************************************************************/
/**** READ ****/
#define 		PLANNER_FUNC_READ_COUNT		9
labelId_t 	Planner_Func_R_labelIds[PLANNER_FUNC_READ_COUNT] = {L_LANE_BOUNDARY, L_OCCUPANCY_GRID, L_MATRIX_SFM, L_BOUNDARY_BOX, L_X_CAR, L_Y_CAR, L_YAW_CAR, L_VEL_CAR, L_YAW_RATE};

uint8_t r_Planner_Func_lane_boundary_buffer[L_LANE_BOUNDARY_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_lane_boundary = {
	.data = r_Planner_Func_lane_boundary_buffer,
	.size = L_LANE_BOUNDARY_SIZE
};

uint8_t r_Planner_Func_occupancy_grid_buffer[L_OCCUPANCY_GRID_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_occupancy_grid = {
	.data = r_Planner_Func_occupancy_grid_buffer,
	.size = L_OCCUPANCY_GRID_SIZE
};

uint8_t r_Planner_Func_matrix_sfm_buffer[L_MATRIX_SFM_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_matrix_sfm = {
	.data = r_Planner_Func_matrix_sfm_buffer,
	.size = L_MATRIX_SFM_SIZE
};

uint8_t r_Planner_Func_boundary_box_buffer[L_BOUNDARY_BOX_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_boundary_box = {
	.data = r_Planner_Func_boundary_box_buffer,
	.size = L_BOUNDARY_BOX_SIZE
};

uint8_t r_Planner_Func_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_x_car = {
	.data = r_Planner_Func_x_car_buffer,
	.size = L_X_CAR_SIZE
};

uint8_t r_Planner_Func_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_y_car = {
	.data = r_Planner_Func_y_car_buffer,
	.size = L_Y_CAR_SIZE
};

uint8_t r_Planner_Func_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_yaw_car = {
	.data = r_Planner_Func_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};

uint8_t r_Planner_Func_vel_car_buffer[L_VEL_CAR_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_vel_car = {
	.data = r_Planner_Func_vel_car_buffer,
	.size = L_VEL_CAR_SIZE
};

uint8_t r_Planner_Func_yaw_rate_buffer[L_YAW_RATE_SIZE];	// Local buffer for label Planner_Func
localLabel_t r_Planner_Func_yaw_rate = {
	.data = r_Planner_Func_yaw_rate_buffer,
	.size = L_YAW_RATE_SIZE
};


localLabel_t* Planner_Func_R_copies[PLANNER_FUNC_READ_COUNT] = {
	&r_Planner_Func_lane_boundary,
	&r_Planner_Func_occupancy_grid,
	&r_Planner_Func_matrix_sfm,
	&r_Planner_Func_boundary_box,
	&r_Planner_Func_x_car,
	&r_Planner_Func_y_car,
	&r_Planner_Func_yaw_car,
	&r_Planner_Func_vel_car,
	&r_Planner_Func_yaw_rate,
};

/**** WRITE ****/
#define 		PLANNER_FUNC_WRITE_COUNT	2
labelId_t 	Planner_Func_W_labelIds[PLANNER_FUNC_WRITE_COUNT] = {L_SPEED_OBJECTIVE, L_STEER_OBJECTIVE};

uint8_t w_Planner_Func_speed_objective_buffer[L_SPEED_OBJECTIVE_SIZE];	// Local buffer for label Planner_Func
localLabel_t w_Planner_Func_speed_objective = {
	.data = w_Planner_Func_speed_objective_buffer,
	.size = L_SPEED_OBJECTIVE_SIZE
};
uint8_t w_Planner_Func_steer_objective_buffer[L_STEER_OBJECTIVE_SIZE];	// Local buffer for label Planner_Func
localLabel_t w_Planner_Func_steer_objective = {
	.data = w_Planner_Func_steer_objective_buffer,
	.size = L_STEER_OBJECTIVE_SIZE
};

localLabel_t* Planner_Func_W_copies[PLANNER_FUNC_WRITE_COUNT] = {
	&w_Planner_Func_speed_objective,
	&w_Planner_Func_steer_objective,
};

/**** CONFIGURATION ****/
runnable_spec_t Planner_Func = {
	.name = "Planner_Func",
	.func = r_Planner_Func,
	.init = r_Planner_Func_init,
	.deinit = r_Planner_Func_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = PLANNER_FUNC_READ_COUNT,
	.inputLabelIds = Planner_Func_R_labelIds,
	.inputData = Planner_Func_R_copies,
	.outputLabelCount = PLANNER_FUNC_WRITE_COUNT,
	.outputLabelIds = Planner_Func_W_labelIds,
	.outputData = Planner_Func_W_copies
};

/**************************************************************************
 * Runnable Rx_Lidar_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** WRITE ****/
#define 		RX_LIDAR_TO_RASPBERRYPI_2_WRITE_COUNT	1
labelId_t 	Rx_Lidar_to_RaspberryPi_2_W_labelIds[RX_LIDAR_TO_RASPBERRYPI_2_WRITE_COUNT] = {L_OCCUPANCY_GRID};

uint8_t w_Rx_Lidar_to_RaspberryPi_2_occupancy_grid_buffer[L_OCCUPANCY_GRID_SIZE];	// Local buffer for label Rx_Lidar_to_RaspberryPi_2
localLabel_t w_Rx_Lidar_to_RaspberryPi_2_occupancy_grid = {
	.data = w_Rx_Lidar_to_RaspberryPi_2_occupancy_grid_buffer,
	.size = L_OCCUPANCY_GRID_SIZE
};

localLabel_t* Rx_Lidar_to_RaspberryPi_2_W_copies[RX_LIDAR_TO_RASPBERRYPI_2_WRITE_COUNT] = {
	&w_Rx_Lidar_to_RaspberryPi_2_occupancy_grid,
};

/**** CONFIGURATION ****/
runnable_spec_t Rx_Lidar_to_RaspberryPi_2 = {
	.name = "Rx_Lidar_to_RaspberryPi_2",
	.func = r_Rx_Lidar_to_RaspberryPi_2,
	.init = r_Rx_Lidar_to_RaspberryPi_2_init,
	.deinit = r_Rx_Lidar_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = RX_LIDAR_TO_RASPBERRYPI_2_WRITE_COUNT,
	.outputLabelIds = Rx_Lidar_to_RaspberryPi_2_W_labelIds,
	.outputData = Rx_Lidar_to_RaspberryPi_2_W_copies
};

/**************************************************************************
 * Runnable Rx_EKF_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** WRITE ****/
#define 		RX_EKF_TO_RASPBERRYPI_2_WRITE_COUNT	5
labelId_t 	Rx_EKF_to_RaspberryPi_2_W_labelIds[RX_EKF_TO_RASPBERRYPI_2_WRITE_COUNT] = {L_X_CAR, L_Y_CAR, L_YAW_CAR, L_VEL_CAR, L_YAW_RATE};

uint8_t w_Rx_EKF_to_RaspberryPi_2_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label Rx_EKF_to_RaspberryPi_2
localLabel_t w_Rx_EKF_to_RaspberryPi_2_x_car = {
	.data = w_Rx_EKF_to_RaspberryPi_2_x_car_buffer,
	.size = L_X_CAR_SIZE
};
uint8_t w_Rx_EKF_to_RaspberryPi_2_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label Rx_EKF_to_RaspberryPi_2
localLabel_t w_Rx_EKF_to_RaspberryPi_2_y_car = {
	.data = w_Rx_EKF_to_RaspberryPi_2_y_car_buffer,
	.size = L_Y_CAR_SIZE
};
uint8_t w_Rx_EKF_to_RaspberryPi_2_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label Rx_EKF_to_RaspberryPi_2
localLabel_t w_Rx_EKF_to_RaspberryPi_2_yaw_car = {
	.data = w_Rx_EKF_to_RaspberryPi_2_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};
uint8_t w_Rx_EKF_to_RaspberryPi_2_vel_car_buffer[L_VEL_CAR_SIZE];	// Local buffer for label Rx_EKF_to_RaspberryPi_2
localLabel_t w_Rx_EKF_to_RaspberryPi_2_vel_car = {
	.data = w_Rx_EKF_to_RaspberryPi_2_vel_car_buffer,
	.size = L_VEL_CAR_SIZE
};
uint8_t w_Rx_EKF_to_RaspberryPi_2_yaw_rate_buffer[L_YAW_RATE_SIZE];	// Local buffer for label Rx_EKF_to_RaspberryPi_2
localLabel_t w_Rx_EKF_to_RaspberryPi_2_yaw_rate = {
	.data = w_Rx_EKF_to_RaspberryPi_2_yaw_rate_buffer,
	.size = L_YAW_RATE_SIZE
};

localLabel_t* Rx_EKF_to_RaspberryPi_2_W_copies[RX_EKF_TO_RASPBERRYPI_2_WRITE_COUNT] = {
	&w_Rx_EKF_to_RaspberryPi_2_x_car,
	&w_Rx_EKF_to_RaspberryPi_2_y_car,
	&w_Rx_EKF_to_RaspberryPi_2_yaw_car,
	&w_Rx_EKF_to_RaspberryPi_2_vel_car,
	&w_Rx_EKF_to_RaspberryPi_2_yaw_rate,
};

/**** CONFIGURATION ****/
runnable_spec_t Rx_EKF_to_RaspberryPi_2 = {
	.name = "Rx_EKF_to_RaspberryPi_2",
	.func = r_Rx_EKF_to_RaspberryPi_2,
	.init = r_Rx_EKF_to_RaspberryPi_2_init,
	.deinit = r_Rx_EKF_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = RX_EKF_TO_RASPBERRYPI_2_WRITE_COUNT,
	.outputLabelIds = Rx_EKF_to_RaspberryPi_2_W_labelIds,
	.outputData = Rx_EKF_to_RaspberryPi_2_W_copies
};

/**************************************************************************
 * Runnable Rx_Detection_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** WRITE ****/
#define 		RX_DETECTION_TO_RASPBERRYPI_2_WRITE_COUNT	1
labelId_t 	Rx_Detection_to_RaspberryPi_2_W_labelIds[RX_DETECTION_TO_RASPBERRYPI_2_WRITE_COUNT] = {L_BOUNDARY_BOX};

uint8_t w_Rx_Detection_to_RaspberryPi_2_boundary_box_buffer[L_BOUNDARY_BOX_SIZE];	// Local buffer for label Rx_Detection_to_RaspberryPi_2
localLabel_t w_Rx_Detection_to_RaspberryPi_2_boundary_box = {
	.data = w_Rx_Detection_to_RaspberryPi_2_boundary_box_buffer,
	.size = L_BOUNDARY_BOX_SIZE
};

localLabel_t* Rx_Detection_to_RaspberryPi_2_W_copies[RX_DETECTION_TO_RASPBERRYPI_2_WRITE_COUNT] = {
	&w_Rx_Detection_to_RaspberryPi_2_boundary_box,
};

/**** CONFIGURATION ****/
runnable_spec_t Rx_Detection_to_RaspberryPi_2 = {
	.name = "Rx_Detection_to_RaspberryPi_2",
	.func = r_Rx_Detection_to_RaspberryPi_2,
	.init = r_Rx_Detection_to_RaspberryPi_2_init,
	.deinit = r_Rx_Detection_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = RX_DETECTION_TO_RASPBERRYPI_2_WRITE_COUNT,
	.outputLabelIds = Rx_Detection_to_RaspberryPi_2_W_labelIds,
	.outputData = Rx_Detection_to_RaspberryPi_2_W_copies
};

/**************************************************************************
 * Runnable Rx_Localization_to_RaspberryPi_2 configuration
 *************************************************************************/
/**** WRITE ****/
#define 		RX_LOCALIZATION_TO_RASPBERRYPI_2_WRITE_COUNT	3
labelId_t 	Rx_Localization_to_RaspberryPi_2_W_labelIds[RX_LOCALIZATION_TO_RASPBERRYPI_2_WRITE_COUNT] = {L_X_CAR, L_Y_CAR, L_YAW_CAR};

uint8_t w_Rx_Localization_to_RaspberryPi_2_x_car_buffer[L_X_CAR_SIZE];	// Local buffer for label Rx_Localization_to_RaspberryPi_2
localLabel_t w_Rx_Localization_to_RaspberryPi_2_x_car = {
	.data = w_Rx_Localization_to_RaspberryPi_2_x_car_buffer,
	.size = L_X_CAR_SIZE
};
uint8_t w_Rx_Localization_to_RaspberryPi_2_y_car_buffer[L_Y_CAR_SIZE];	// Local buffer for label Rx_Localization_to_RaspberryPi_2
localLabel_t w_Rx_Localization_to_RaspberryPi_2_y_car = {
	.data = w_Rx_Localization_to_RaspberryPi_2_y_car_buffer,
	.size = L_Y_CAR_SIZE
};
uint8_t w_Rx_Localization_to_RaspberryPi_2_yaw_car_buffer[L_YAW_CAR_SIZE];	// Local buffer for label Rx_Localization_to_RaspberryPi_2
localLabel_t w_Rx_Localization_to_RaspberryPi_2_yaw_car = {
	.data = w_Rx_Localization_to_RaspberryPi_2_yaw_car_buffer,
	.size = L_YAW_CAR_SIZE
};

localLabel_t* Rx_Localization_to_RaspberryPi_2_W_copies[RX_LOCALIZATION_TO_RASPBERRYPI_2_WRITE_COUNT] = {
	&w_Rx_Localization_to_RaspberryPi_2_x_car,
	&w_Rx_Localization_to_RaspberryPi_2_y_car,
	&w_Rx_Localization_to_RaspberryPi_2_yaw_car,
};

/**** CONFIGURATION ****/
runnable_spec_t Rx_Localization_to_RaspberryPi_2 = {
	.name = "Rx_Localization_to_RaspberryPi_2",
	.func = r_Rx_Localization_to_RaspberryPi_2,
	.init = r_Rx_Localization_to_RaspberryPi_2_init,
	.deinit = r_Rx_Localization_to_RaspberryPi_2_deinit,
	.initialized = false,
	.mode = 0,
	.var = 0.0,
	.user_data = NULL,
	.inputLabelCount = 0,
	.inputLabelIds = NULL,
	.inputData = NULL,
	.outputLabelCount = RX_LOCALIZATION_TO_RASPBERRYPI_2_WRITE_COUNT,
	.outputLabelIds = Rx_Localization_to_RaspberryPi_2_W_labelIds,
	.outputData = Rx_Localization_to_RaspberryPi_2_W_copies
};

#endif //USER_RUNNABLES_H
