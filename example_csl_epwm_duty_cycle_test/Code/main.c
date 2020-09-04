/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/csl/csl_epwm.h>


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

/* User Include */
#include "epwm_app.h"

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

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    System_printf("enter taskFxn()\n");

	initBbbDevice();
	
    Task_sleep(10);

	(void) test_csl_epwm_duty_cycle_test_app_runner();
	while (1)
	{
	}

    System_printf("exit taskFxn()\n");

    System_flush(); /* force SysMin output to console */
}

/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;
    Error_Block eb;

    System_printf("enter main()\n");

    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
