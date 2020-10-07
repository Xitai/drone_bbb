/*
 * bbb_i2c.c
 *
 *  Created on: 2020. 8. 14.
 *      Author: AWT
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* UART Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/test/src/UART_board.h>

#include "bbb_i2c.h"

#include "bbb_hw.h"

#define I2C_EEPROM_INSTANCE      2//BOARD_I2C_EEPROM_INSTANCE

#define I2C_EEPROM_TEST_LENGTH   		1  			/* Read (and write) test in bytes */
#define I2C_EEPROM_ADDR          		(0x68)		//BOARD_I2C_EEPROM_ADDR
#define I2C_EEPROM_ADDR_SIZE     		1   		/* in bytes */
#define I2C_TRANSACTION_TIMEOUT         (20000U)
#define I2C_EEPROM_TEST_ADDR            (0x00)

#define I2C_log                	UART_printf

extern uint8_t I2C_Address;

unsigned long i2c_master_read_register(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, unsigned char *RegisterValue)
{
    I2C_Params      i2cParams;
    I2C_Handle      handle = NULL;
    I2C_Transaction i2cTransaction;
    char            txBuf[I2C_EEPROM_TEST_LENGTH + I2C_EEPROM_ADDR_SIZE] = {0x00, };
    //char            rxBuf[64];
    int16_t         status;
    unsigned long   ulResult = 0;
    I2C_HwAttrs   i2c_cfg;

    I2C_socGetInitCfg(I2C_EEPROM_INSTANCE, &i2c_cfg);

    i2c_cfg.enableIntr = true;

    I2C_socSetInitCfg(I2C_EEPROM_INSTANCE, &i2c_cfg);

    I2C_Params_init(&i2cParams);

    i2cParams.bitRate = 1;

    handle = I2C_open(I2C_EEPROM_INSTANCE, &i2cParams);
    if (handle != NULL)
    {
        txBuf[0] = RegisterAddr;
        //memset(rxBuf, 0, I2C_EEPROM_TEST_LENGTH);

        I2C_transactionInit(&i2cTransaction);

        i2cTransaction.slaveAddress = Address;
        i2cTransaction.writeBuf = (uint8_t *)&txBuf[0];
        i2cTransaction.writeCount = I2C_EEPROM_ADDR_SIZE;
        i2cTransaction.readBuf = RegisterValue;
        i2cTransaction.readCount = RegisterLen;
        i2cTransaction.timeout   = I2C_TRANSACTION_TIMEOUT;

        status = I2C_transfer(handle, &i2cTransaction);

        if(I2C_STS_SUCCESS != status)
        {
            I2C_log("[E]I2C Read Data Transfer failed. \n");
            ulResult = 1; // error
        }
//        else
//        {
//            I2C_log("[D]I2C Read: ");
//            I2C_log("%02X\n", RegisterValue[0]);
//
//            ulResult = 0;
//        }

        I2C_close(handle);
    }

	return ulResult; // temp 2020-06-11
}

unsigned long i2c_master_write_register(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, const unsigned char *RegisterValue)
{
   I2C_Params      i2cParams;
   I2C_Handle      handle = NULL;
   I2C_Transaction i2cTransaction;
   char            txBuf[128] = {0x00, };
   //char            rxBuf[64];
   int16_t         status;
  // int32_t          iIdx = 0;
   unsigned long   ulResult = 0;

   I2C_HwAttrs   i2c_cfg;

   I2C_socGetInitCfg(I2C_EEPROM_INSTANCE, &i2c_cfg);

   i2c_cfg.enableIntr = true;

   I2C_socSetInitCfg(I2C_EEPROM_INSTANCE, &i2c_cfg);

   I2C_Params_init(&i2cParams);

   i2cParams.bitRate = 1;

   handle = I2C_open(I2C_EEPROM_INSTANCE, &i2cParams);
   if (handle != NULL)
   {
       txBuf[0] = RegisterAddr;

       if(RegisterLen > 127)
       {
           I2C_log("[E]I2C Write Data Size Error. \n");
           return 0;
       }
       memcpy((void *)&txBuf[1], (void *)RegisterValue, RegisterLen);

       I2C_transactionInit(&i2cTransaction);

       i2cTransaction.slaveAddress = Address;
       i2cTransaction.writeBuf = (uint8_t *)&txBuf[0];
       i2cTransaction.writeCount = I2C_EEPROM_ADDR_SIZE + RegisterLen;
       i2cTransaction.readBuf = NULL;
       i2cTransaction.readCount = 0;
       i2cTransaction.timeout   = I2C_TRANSACTION_TIMEOUT;

       status = I2C_transfer(handle, &i2cTransaction);

       if(I2C_STS_SUCCESS != status)
       {
           I2C_log("[E]I2C Write Data Transfer failed. \n");
           ulResult = 1;
       }
       //else
       //{
       //    I2C_log("[D]I2C Write(%d): ", I2C_EEPROM_ADDR_SIZE + RegisterLen);
       //
       //    for(iIdx=0; iIdx < I2C_EEPROM_ADDR_SIZE + RegisterLen; iIdx++)
       //    {
       //        I2C_log("%02X ", txBuf[iIdx]);
       //    }
       //
       //    I2C_log("\n");
       //}

       I2C_close(handle);
   }

	
	return ulResult; // temp 2020-06-11
}

int idd_io_hal_read_reg(void * context, uint8_t reg, uint8_t * rbuffer, uint32_t rlen)
{
	(void)context;
	return i2c_master_read_register(I2C_Address, reg, rlen, rbuffer);
}

int idd_io_hal_write_reg(void * context, uint8_t reg, const uint8_t * wbuffer, uint32_t wlen)
{
	(void)context;
	return i2c_master_write_register(I2C_Address, reg, wlen, wbuffer);
}




