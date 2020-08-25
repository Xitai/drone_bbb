/*
 * bbb_hw.c
 *
 *  Created on: 2020. 7. 17.
 *      Author: AWT
 *
 * Description: GPIO, I2C, PWM Configuration
 *
 */

//#include <evmAM335x.h>
//#include <soc_AM335x.h>
//#include <interrupt.h>
//#include <hw_control_AM335x.h>
//#include <hw_cm_per.h>
//#include <pin_mux.h>
//#include <gpio_v2.h>
//#include <consoleUtils.h>
//#include <hsi2c.h>


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>

///* UART Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/test/src/UART_board.h>

///* I2C header files */
#include <ti/drv/i2c/I2C.h>
#include <ti/drv/i2c/soc/I2C_soc.h>
#include <ti/csl/soc.h>
#include <ti/starterware/include/hw/soc_am335x.h>

#include "bbb_hw.h"
#include "bbb_intr.h"
//#include "icm20948_twi.h"

//############################### DEFINES ##################################
/* GPIO Defines */
#define GPIO_USER0_IMU_INTR_PIN_NUM    (13)
#define GPIO_USER0_IMU_INTR_PORT_NUM   (1)


//############################### GLOBAL VARIABLES ##################################
/*************************************************
 *		GPIO Global Variables
 */
 
 
/* GPIO Driver board specific pin configuration structure */
GPIO_PinConfig gpioPinConfigs[] = {
    /* Input pin with interrupt enabled : User LED */
    GPIO_DEVICE_CONFIG((GPIO_USER0_IMU_INTR_PORT_NUM + 1), GPIO_USER0_IMU_INTR_PIN_NUM) |
    GPIO_CFG_IN_INT_RISING | GPIO_CFG_INPUT

//    /* Output pin : User LED */
//    GPIO_DEVICE_CONFIG((GPIO_USER0_LED_PORT_NUM + 1), GPIO_USER0_LED_PIN_NUM) |
//    GPIO_CFG_OUTPUT
};

/* GPIO Driver call back functions */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL
//    NULL
};

/* GPIO Driver configuration structure */
GPIO_v1_Config GPIO_v1_config = {
    gpioPinConfigs,
    gpioCallbackFunctions,
    sizeof(gpioPinConfigs) / sizeof(GPIO_PinConfig),
    sizeof(gpioCallbackFunctions) / sizeof(GPIO_CallbackFxn),
    0x1U,
    };


//############################### FUNCTIONS ################################

/*************************************************
 *		Board Initialize 
 */
bool initBbbDevice(void)
{
	Board_initCfg boardCfg;
	Board_STATUS  boardStatus;
	
    boardCfg = BOARD_INIT_PINMUX_CONFIG |
               BOARD_INIT_MODULE_CLOCK  |
               BOARD_INIT_UART_STDIO;
	
	boardStatus = Board_init(boardCfg);
    if (boardStatus != BOARD_SOK)
    {
        return (false);
    }
	
	
	return (true);
}

/*************************************************
 *		GPIO Initialize
 */
void initBbbGpio(void)
{
    GPIO_init();

    /* Set the callback function */
    GPIO_setCallback(0, icm20948_GPIOIsr);

    /* Enable GPIO interrupt on the specific gpio pin */
    GPIO_enableInt(0);

    /* Write high to gpio pin to control LED1 */
    //GPIO_write((USER_LED1), GPIO_PIN_VAL_HIGH);
    //AppDelay(DELAY_VALUE);

}

//
//void ext_intr_init(void)
//{
//	//I2CAINTCConfigure();
//	 /* Intialize the ARM Interrupt Controller(AINTC) */
//    IntAINTCInit();
//
//    /* Registering the Interrupt Service Routine(ISR). */
//    IntRegister(SYS_INT_I2C2INT, icm20948_I2CIsr);
//	
//    /* Setting the priority for the system interrupt in AINTC. */
//    IntPrioritySet(SYS_INT_I2C2INT, 1, AINTC_HOSTINT_ROUTE_IRQ );
//	
//	
//	
//	
//	/* Register the Interrupt Service Routine(ISR). */
//    IntRegister(SYS_INT_GPIOINT1A, icm20948_GPIOIsr);
//	
//    /* Set the priority for the GPIO0 system interrupt in INTC. */
//    IntPrioritySet(SYS_INT_GPIOINT1A, 0, AINTC_HOSTINT_ROUTE_IRQ);
//		
//		
//	/* Enabling the system interrupt in AINTC. */
//    IntSystemEnable(SYS_INT_I2C2INT);
//	
//    /* Enable the GPIO0 system interrupt in INTC. */
//    IntSystemEnable(SYS_INT_GPIOINT1A);
//
//	
//}
