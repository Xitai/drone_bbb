/*
 * bbb_i2c.h
 *
 *  Created on: 2020. 8. 14.
 *      Author: AWT
 */

#ifndef CODE_INCLUDE_BBB_I2C_H_
#define CODE_INCLUDE_BBB_I2C_H_

#include <stdint.h>

/* I2C header files */
#include <ti/drv/i2c/I2C.h>
#include <ti/drv/i2c/soc/I2C_soc.h>
#include <ti/csl/soc.h>
#include <ti/starterware/include/hw/soc_am335x.h>

//I2C_Handle openImuI2c(void);
unsigned long i2c_master_read_register(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, unsigned char *RegisterValue);
unsigned long i2c_master_write_register(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, const unsigned char *RegisterValue);
int idd_io_hal_read_reg(void * context, uint8_t reg, uint8_t * rbuffer, uint32_t rlen);
int idd_io_hal_write_reg(void * context, uint8_t reg, const uint8_t * wbuffer, uint32_t wlen);


#endif /* CODE_INCLUDE_BBB_I2C_H_ */
