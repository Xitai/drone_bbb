/*
 * icm20948.h
 *
 *  Created on: 2020. 7. 9.
 *      Author: AWT
 */

#ifndef CODE_HEADERS_ICM20948_H_
#define CODE_HEADERS_ICM20948_H_

#include "Devices/Drivers/ICM20948/Icm20948.h"
#include "Devices/SensorTypes.h"

#define AK0991x_DEFAULT_I2C_ADDR	0x0C

/**********************************
 *		Predefines
 */
//#define SERIF_TYPE_I2C (1)
//#define INV_MSG_ENABLE INV_MSG_LEVEL_DEBUG

/**********************************
 *		Structures
 */


/**********************************
 *		Global Variables
 */
extern volatile int irq_from_device;
extern struct inv_icm20948_serif gstIcm20948_serif; // 통신설정
extern inv_sensor_event_t gstImuEvent;

/**********************************
 *		Host System Functions
 */
void icm20948_GPIOIsr(void);
void icm20948_ext_int_initialize(void);
//void icm20948_SetupI2C(void); // interface_initialize();	 과 동일

/**********************************
 *		ICM20948 Board Functions
 */ 
// inv_icm20948_reset_states() // Icm20948.h 참조

/**********************************
 *		Runtime Operation Functions
 */
int icm20948_Setup(void);
int icm20948_WhoAmI(void);
int icm20948_Reset(void);
int icm20948_SelfTest(int sensor_id);
int icm20948_StartSensor(int sensor_id);
int icm20948_StopSensor(int sensor_id);
int icm20948_SetSensorPeriod(int sensor_id, uint32_t uiPeriod);
int icm20948_SetSensorCfg(int sensor_id);
int icm20948_CleanUp(void);
int icm20948_sensor_setup(void);
int load_dmp3(void);
void check_rc(int rc, const char * msg_context);
void build_sensor_event_data(void * context, uint8_t sensortype, uint64_t timestamp, const void * data, const void *arg);

/* User Customized Functions */

int userSetup(void);
int userWhoAmI(void);
int userReset(void);
int userSelfTest(int sensor_id);
int userStartSensor(int sensor_id);
int userStopSensor(int sensor_id);
int userSetSensorPeriod(int sensor_id, uint32_t uiPeriod);
int userSetSensorCfg(int sensor_id);
int userCleanUp(void);

#endif /* CODE_HEADERS_ICM20948_H_ */
