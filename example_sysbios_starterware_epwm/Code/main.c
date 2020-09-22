/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

//#include <ti/csl/csl_epwm.h>


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
//#include <ti/csl/soc.h>
#include <ti/starterware/include/hw/soc_am335x.h>

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "types.h"
#include "error.h"
#include "board.h"
#include "soc.h"
#include "device.h"
#include "chipdb.h"
#include "cache.h"
#include "mmu.h"
#include "example_utils_mmu.h"
#include "console_utils.h"

/* Application header files */
#include "epwm_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */


/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API gets the soc info - base address of epwm instance.
 *
 * \param   pObj     Pointer to the pwm object.
 *
 * \retval  S_PASS   SOC info is successfully retrieved.
 * \retval  E_FAIL   SOC info retrieval is failed. Resource is not present.
 */
static uint32_t EpwmAppSocInfoGet(epwmAppPwmObj_t *pObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Global object for the EPWM IP configuration data structure.  */
static epwmAppPwmObj_t gPwmCfg;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


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
 *		EPWM Task Function
 */
Void taskFxn(UArg a0, UArg a1)
{
    System_printf("enter taskFxn()\n");

	initBbbDevice();
	
    Task_sleep(10);
	
	/*********************************************************************
	 * 						START EPWM
	 */
	
    int32_t status = S_PASS;


    /* Initialize the global IP configuration with default configuration. */
    gPwmCfg     = CONF_EPWM1_MOTOR;

    UART_printf("\n StarterWare EPWM Application!!\n");
    UART_printf("BOARDInit status [0x%x]\n", status);

	/* Get SoC info */
	status = EpwmAppSocInfoGet(&gPwmCfg);
	if(S_PASS == status)
	{
		/* EPWM IP configuration */
		status = EPWMAppInit(&gPwmCfg);
		if(S_PASS == status)
		{
			UART_printf("\nNow running the haptics motor ...\n");
			while(1)
			{
				/* Infinite loop */
			}
		}
		else
		{
			UART_printf("\n FAILURE!!! EPWM IP configuration is failed ...\n");
		}
	}
	else
	{
		UART_printf("\nEPWM IP instance is not present ...\n");
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



/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t EpwmAppSocInfoGet(epwmAppPwmObj_t *pObj)
{
    uint32_t status = S_PASS;

    /* Get the base address of the Module */
    if(TRUE == CHIPDBIsResourcePresent(CHIPDB_MOD_ID_PWMSS, pObj->instNum))
    {
        pObj->instAddr = CHIPDBBaseAddress(CHIPDB_MOD_ID_PWMSS, pObj->instNum);
    }
    else
    {
       UART_printf("PWMSS instance number is not present!\n");
       status = E_FAIL;
    }

    return status;
}

