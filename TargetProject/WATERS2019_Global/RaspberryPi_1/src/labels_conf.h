#ifndef LABELS_CONF_H_
#define LABELS_CONF_H_

#include "labels.h"

#define LABELS_COUNT	16

#define L_CLOUD_MAP 0
#define L_OCCUPANCY_GRID 1
#define L_VEHICLE_STATUS 2
#define L_X_CAR 3
#define L_Y_CAR 4
#define L_YAW_CAR 5
#define L_VEL_CAR 6
#define L_YAW_RATE 7
#define L_STEER_OBJECTIVE 8
#define L_SPEED_OBJECTIVE 9
#define L_IMAGE 10
#define L_MATRIX_SFM 11
#define L_BOUNDARY_BOX 12
#define L_LANE_BOUNDARY 13
#define L_IMAGE_LANE 14
#define L_IMAGE_SFM 15

/**
 * Label CLOUD_MAP
 */
#define L_CLOUD_MAP_SIZE 1500000

extern uint8_t l_cloud_map_dataA[L_CLOUD_MAP_SIZE];
extern uint8_t l_cloud_map_dataB[L_CLOUD_MAP_SIZE];

extern globalLabel_t l_cloud_map;

/**
 * Label OCCUPANCY_GRID
 */
#define L_OCCUPANCY_GRID_SIZE 500000

extern uint8_t l_occupancy_grid_dataA[L_OCCUPANCY_GRID_SIZE];
extern uint8_t l_occupancy_grid_dataB[L_OCCUPANCY_GRID_SIZE];

extern globalLabel_t l_occupancy_grid;

/**
 * Label VEHICLE_STATUS
 */
#define L_VEHICLE_STATUS_SIZE 1000

extern uint8_t l_vehicle_status_dataA[L_VEHICLE_STATUS_SIZE];
extern uint8_t l_vehicle_status_dataB[L_VEHICLE_STATUS_SIZE];

extern globalLabel_t l_vehicle_status;

/**
 * Label X_CAR
 */
#define L_X_CAR_SIZE 1000

extern uint8_t l_x_car_dataA[L_X_CAR_SIZE];
extern uint8_t l_x_car_dataB[L_X_CAR_SIZE];

extern globalLabel_t l_x_car;

/**
 * Label Y_CAR
 */
#define L_Y_CAR_SIZE 1000

extern uint8_t l_y_car_dataA[L_Y_CAR_SIZE];
extern uint8_t l_y_car_dataB[L_Y_CAR_SIZE];

extern globalLabel_t l_y_car;

/**
 * Label YAW_CAR
 */
#define L_YAW_CAR_SIZE 1000

extern uint8_t l_yaw_car_dataA[L_YAW_CAR_SIZE];
extern uint8_t l_yaw_car_dataB[L_YAW_CAR_SIZE];

extern globalLabel_t l_yaw_car;

/**
 * Label VEL_CAR
 */
#define L_VEL_CAR_SIZE 1000

extern uint8_t l_vel_car_dataA[L_VEL_CAR_SIZE];
extern uint8_t l_vel_car_dataB[L_VEL_CAR_SIZE];

extern globalLabel_t l_vel_car;

/**
 * Label YAW_RATE
 */
#define L_YAW_RATE_SIZE 1000

extern uint8_t l_yaw_rate_dataA[L_YAW_RATE_SIZE];
extern uint8_t l_yaw_rate_dataB[L_YAW_RATE_SIZE];

extern globalLabel_t l_yaw_rate;

/**
 * Label STEER_OBJECTIVE
 */
#define L_STEER_OBJECTIVE_SIZE 1000

extern uint8_t l_steer_objective_dataA[L_STEER_OBJECTIVE_SIZE];
extern uint8_t l_steer_objective_dataB[L_STEER_OBJECTIVE_SIZE];

extern globalLabel_t l_steer_objective;

/**
 * Label SPEED_OBJECTIVE
 */
#define L_SPEED_OBJECTIVE_SIZE 1000

extern uint8_t l_speed_objective_dataA[L_SPEED_OBJECTIVE_SIZE];
extern uint8_t l_speed_objective_dataB[L_SPEED_OBJECTIVE_SIZE];

extern globalLabel_t l_speed_objective;

/**
 * Label IMAGE
 */
#define L_IMAGE_SIZE 2000000

extern uint8_t l_image_dataA[L_IMAGE_SIZE];
extern uint8_t l_image_dataB[L_IMAGE_SIZE];

extern globalLabel_t l_image;

/**
 * Label MATRIX_SFM
 */
#define L_MATRIX_SFM_SIZE 24000

extern uint8_t l_matrix_sfm_dataA[L_MATRIX_SFM_SIZE];
extern uint8_t l_matrix_sfm_dataB[L_MATRIX_SFM_SIZE];

extern globalLabel_t l_matrix_sfm;

/**
 * Label BOUNDARY_BOX
 */
#define L_BOUNDARY_BOX_SIZE 750000

extern uint8_t l_boundary_box_dataA[L_BOUNDARY_BOX_SIZE];
extern uint8_t l_boundary_box_dataB[L_BOUNDARY_BOX_SIZE];

extern globalLabel_t l_boundary_box;

/**
 * Label LANE_BOUNDARY
 */
#define L_LANE_BOUNDARY_SIZE 256

extern uint8_t l_lane_boundary_dataA[L_LANE_BOUNDARY_SIZE];
extern uint8_t l_lane_boundary_dataB[L_LANE_BOUNDARY_SIZE];

extern globalLabel_t l_lane_boundary;

/**
 * Label IMAGE_LANE
 */
#define L_IMAGE_LANE_SIZE 2000000

extern uint8_t l_image_lane_dataA[L_IMAGE_LANE_SIZE];
extern uint8_t l_image_lane_dataB[L_IMAGE_LANE_SIZE];

extern globalLabel_t l_image_lane;

/**
 * Label IMAGE_SFM
 */
#define L_IMAGE_SFM_SIZE 2000000

extern uint8_t l_image_sfm_dataA[L_IMAGE_SFM_SIZE];
extern uint8_t l_image_sfm_dataB[L_IMAGE_SFM_SIZE];

extern globalLabel_t l_image_sfm;



extern globalLabel_t* labels[LABELS_COUNT];

#endif //LABELS_CONF_H_
