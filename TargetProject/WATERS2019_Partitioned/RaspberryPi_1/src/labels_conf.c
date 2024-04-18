#include "labels_conf.h"

/**
 * Label CLOUD_MAP
 */

uint8_t l_cloud_map_dataA[L_CLOUD_MAP_SIZE];
uint8_t l_cloud_map_dataB[L_CLOUD_MAP_SIZE];

globalLabel_t l_cloud_map = {
	.readpos = 0,
	.dataA = l_cloud_map_dataA,
	.dataB = l_cloud_map_dataB,
	.size = L_CLOUD_MAP_SIZE
};

/**
 * Label OCCUPANCY_GRID
 */

uint8_t l_occupancy_grid_dataA[L_OCCUPANCY_GRID_SIZE];
uint8_t l_occupancy_grid_dataB[L_OCCUPANCY_GRID_SIZE];

globalLabel_t l_occupancy_grid = {
	.readpos = 0,
	.dataA = l_occupancy_grid_dataA,
	.dataB = l_occupancy_grid_dataB,
	.size = L_OCCUPANCY_GRID_SIZE
};

/**
 * Label VEHICLE_STATUS
 */

uint8_t l_vehicle_status_dataA[L_VEHICLE_STATUS_SIZE];
uint8_t l_vehicle_status_dataB[L_VEHICLE_STATUS_SIZE];

globalLabel_t l_vehicle_status = {
	.readpos = 0,
	.dataA = l_vehicle_status_dataA,
	.dataB = l_vehicle_status_dataB,
	.size = L_VEHICLE_STATUS_SIZE
};

/**
 * Label X_CAR
 */

uint8_t l_x_car_dataA[L_X_CAR_SIZE];
uint8_t l_x_car_dataB[L_X_CAR_SIZE];

globalLabel_t l_x_car = {
	.readpos = 0,
	.dataA = l_x_car_dataA,
	.dataB = l_x_car_dataB,
	.size = L_X_CAR_SIZE
};

/**
 * Label Y_CAR
 */

uint8_t l_y_car_dataA[L_Y_CAR_SIZE];
uint8_t l_y_car_dataB[L_Y_CAR_SIZE];

globalLabel_t l_y_car = {
	.readpos = 0,
	.dataA = l_y_car_dataA,
	.dataB = l_y_car_dataB,
	.size = L_Y_CAR_SIZE
};

/**
 * Label YAW_CAR
 */

uint8_t l_yaw_car_dataA[L_YAW_CAR_SIZE];
uint8_t l_yaw_car_dataB[L_YAW_CAR_SIZE];

globalLabel_t l_yaw_car = {
	.readpos = 0,
	.dataA = l_yaw_car_dataA,
	.dataB = l_yaw_car_dataB,
	.size = L_YAW_CAR_SIZE
};

/**
 * Label VEL_CAR
 */

uint8_t l_vel_car_dataA[L_VEL_CAR_SIZE];
uint8_t l_vel_car_dataB[L_VEL_CAR_SIZE];

globalLabel_t l_vel_car = {
	.readpos = 0,
	.dataA = l_vel_car_dataA,
	.dataB = l_vel_car_dataB,
	.size = L_VEL_CAR_SIZE
};

/**
 * Label YAW_RATE
 */

uint8_t l_yaw_rate_dataA[L_YAW_RATE_SIZE];
uint8_t l_yaw_rate_dataB[L_YAW_RATE_SIZE];

globalLabel_t l_yaw_rate = {
	.readpos = 0,
	.dataA = l_yaw_rate_dataA,
	.dataB = l_yaw_rate_dataB,
	.size = L_YAW_RATE_SIZE
};

/**
 * Label STEER_OBJECTIVE
 */

uint8_t l_steer_objective_dataA[L_STEER_OBJECTIVE_SIZE];
uint8_t l_steer_objective_dataB[L_STEER_OBJECTIVE_SIZE];

globalLabel_t l_steer_objective = {
	.readpos = 0,
	.dataA = l_steer_objective_dataA,
	.dataB = l_steer_objective_dataB,
	.size = L_STEER_OBJECTIVE_SIZE
};

/**
 * Label SPEED_OBJECTIVE
 */

uint8_t l_speed_objective_dataA[L_SPEED_OBJECTIVE_SIZE];
uint8_t l_speed_objective_dataB[L_SPEED_OBJECTIVE_SIZE];

globalLabel_t l_speed_objective = {
	.readpos = 0,
	.dataA = l_speed_objective_dataA,
	.dataB = l_speed_objective_dataB,
	.size = L_SPEED_OBJECTIVE_SIZE
};

/**
 * Label IMAGE
 */

uint8_t l_image_dataA[L_IMAGE_SIZE];
uint8_t l_image_dataB[L_IMAGE_SIZE];

globalLabel_t l_image = {
	.readpos = 0,
	.dataA = l_image_dataA,
	.dataB = l_image_dataB,
	.size = L_IMAGE_SIZE
};

/**
 * Label MATRIX_SFM
 */

uint8_t l_matrix_sfm_dataA[L_MATRIX_SFM_SIZE];
uint8_t l_matrix_sfm_dataB[L_MATRIX_SFM_SIZE];

globalLabel_t l_matrix_sfm = {
	.readpos = 0,
	.dataA = l_matrix_sfm_dataA,
	.dataB = l_matrix_sfm_dataB,
	.size = L_MATRIX_SFM_SIZE
};

/**
 * Label BOUNDARY_BOX
 */

uint8_t l_boundary_box_dataA[L_BOUNDARY_BOX_SIZE];
uint8_t l_boundary_box_dataB[L_BOUNDARY_BOX_SIZE];

globalLabel_t l_boundary_box = {
	.readpos = 0,
	.dataA = l_boundary_box_dataA,
	.dataB = l_boundary_box_dataB,
	.size = L_BOUNDARY_BOX_SIZE
};

/**
 * Label LANE_BOUNDARY
 */

uint8_t l_lane_boundary_dataA[L_LANE_BOUNDARY_SIZE];
uint8_t l_lane_boundary_dataB[L_LANE_BOUNDARY_SIZE];

globalLabel_t l_lane_boundary = {
	.readpos = 0,
	.dataA = l_lane_boundary_dataA,
	.dataB = l_lane_boundary_dataB,
	.size = L_LANE_BOUNDARY_SIZE
};

/**
 * Label IMAGE_LANE
 */

uint8_t l_image_lane_dataA[L_IMAGE_LANE_SIZE];
uint8_t l_image_lane_dataB[L_IMAGE_LANE_SIZE];

globalLabel_t l_image_lane = {
	.readpos = 0,
	.dataA = l_image_lane_dataA,
	.dataB = l_image_lane_dataB,
	.size = L_IMAGE_LANE_SIZE
};

/**
 * Label IMAGE_SFM
 */

uint8_t l_image_sfm_dataA[L_IMAGE_SFM_SIZE];
uint8_t l_image_sfm_dataB[L_IMAGE_SFM_SIZE];

globalLabel_t l_image_sfm = {
	.readpos = 0,
	.dataA = l_image_sfm_dataA,
	.dataB = l_image_sfm_dataB,
	.size = L_IMAGE_SFM_SIZE
};



globalLabel_t* labels[LABELS_COUNT] = {
	&l_cloud_map,
	&l_occupancy_grid,
	&l_vehicle_status,
	&l_x_car,
	&l_y_car,
	&l_yaw_car,
	&l_vel_car,
	&l_yaw_rate,
	&l_steer_objective,
	&l_speed_objective,
	&l_image,
	&l_matrix_sfm,
	&l_boundary_box,
	&l_lane_boundary,
	&l_image_lane,
	&l_image_sfm,
};

