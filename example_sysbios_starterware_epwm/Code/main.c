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
#include "haptics_motor_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief HAPTICS device instance number */
#define EPWM_HAPTICS_INST_NUM     (0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API gets the board info like PWM channel [A or B] and instance.
 *
 * \param   pObj     Pointer to the pin object.
 *
 * \retval  S_PASS   Board info successful retrieved. Haptics motor is
 *                   connected to EPWM on this board.
 * \retval  E_FAIL   This board does not support this application.
 *                   - Haptics motor device may not be available on this board.
 *                   - Haptics motor may not be connected to EPWM on this board.
 */
static int32_t EpwmAppBoardInfoGet(epwmAppPwmObj_t *pObj);

/**
 * \brief   This API gets the soc info - base address of epwm instance.
 *
 * \param   pObj     Pointer to the pwm object.
 *
 * \retval  S_PASS   SOC info is successfully retrieved.
 * \retval  E_FAIL   SOC info retrieval is failed. Resource is not present.
 */
static uint32_t EpwmAppSocInfoGet(epwmAppPwmObj_t *pObj);

/**
 * \brief   This API sets the default configuration for entire EPWM sub-module.
 *
 * \param   pPwm        Pointer to the pwm object.
 * \param   pHaptics    Pointer to haptics motor use case data structure.
 */
static void EpwmAppUpdateCfgParams(epwmAppPwmObj_t *pPwm,
                                   epwmAppHapticsCfg_t *pHaptics);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Application Use Case default configuration */
static const epwmAppHapticsCfg_t EPWMAPPHAPTICSCFG_DEFAULT =
{
        10U * FREQ_MHZ, /* tbClk */
        20U * FREQ_KHZ, /* pwmFreq */
        FALSE, /* enableDeadband */
        FALSE, /* enableChopper */
        FALSE, /* enableTripzone */
        FALSE, /* enableEventTrigger */
        FALSE  /* enableHighResolution */
};


/** \brief Global object for the EPWM Haptics motor Use case data structure.  */
static epwmAppHapticsCfg_t gHapticsCfg;

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

    /* Enable cache memory and MMU */
    //MMUConfigAndEnable();
    //CACHEEnable(CACHE_IDCACHE, CACHE_INNER_OUTER);

    /* Initialize the Haptics motor use case object with default values. */
    gHapticsCfg = EPWMAPPHAPTICSCFG_DEFAULT;

    /* Initialize the global IP configuration with default configuration. */
    gPwmCfg     = EPWMAPPPWMOBJ_DEFAULT;

//    status = BOARDInit(NULL);

    /* Initialize the UART console */
//    CONSOLEUtilsInit();

    /* Select the console type based on compile time check */
//    CONSOLEUtilsSetType(CONSOLE_UTILS_TYPE_UART);

    UART_printf("\n StarterWare EPWM Application!!\n");
    UART_printf("BOARDInit status [0x%x]\n", status);

    /* Print SoC & Board Information. */
    //SOCPrintInfo();
    //BOARDPrintInfo();

    /* Get board info */
    status = EpwmAppBoardInfoGet(&gPwmCfg);
    if (S_PASS == status)
    {
        /* Get SoC info */
        status = EpwmAppSocInfoGet(&gPwmCfg);
        if(S_PASS == status)
        {
            /* EPWM Default configuration */
            EpwmAppUpdateCfgParams(&gPwmCfg, &gHapticsCfg);

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
                UART_printf
                    ("\n FAILURE!!! EPWM IP configuration is failed ...\n");
            }
        }
        else
        {
            UART_printf("\nEPWM IP instance is not present ...\n");
        }
    }
    else
    {
        UART_printf("This example is not supported on this board!\n");
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

static int32_t EpwmAppBoardInfoGet(epwmAppPwmObj_t *pObj)
{
    int32_t status = E_FAIL;
//    chipdbModuleID_t modId;
//    uint32_t  epwmInstNum;
//    uint32_t  epwmOutputCh;
//
//    /* Get the PWMSS[EPWM] data for HAPTICS MOTOR from the board data */
//    modId = BOARDGetDeviceCtrlModId(DEVICE_ID_HAPTICS, EPWM_HAPTICS_INST_NUM);
//    if (CHIPDB_MOD_ID_INVALID == modId)
//    {
//        UART_printf("Device is not available on this board!\n");
//    }
//    else if (CHIPDB_MOD_ID_PWMSS == modId)
//    {
//        epwmInstNum = BOARDGetDeviceCtrlModInstNum(DEVICE_ID_HAPTICS,
//            EPWM_HAPTICS_INST_NUM);
//        epwmOutputCh = BOARDGetDeviceCtrlInfo(DEVICE_ID_HAPTICS,
//            EPWM_HAPTICS_INST_NUM);
//
//        if ((INVALID_INST_NUM == epwmInstNum) || (INVALID_INFO == epwmOutputCh))
//        {
//            UART_printf("Invalid EPWM board data!\n");
//        }
//        else
//        {
//            UART_printf("EPWM Instance number: %d\n", epwmInstNum);
//            UART_printf("EPWM Output Channel : %d\n", epwmOutputCh);
            pObj->instNum = 2U; 
            pObj->pwmCh   = 0U;
            status = S_PASS;
//        }
//    }
//    else
//    {
//        UART_printf("Device is not connected to EPWM!\n");
//    }

    return (status);
}

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

static void EpwmAppUpdateCfgParams(epwmAppPwmObj_t *pPwm,
                                   epwmAppHapticsCfg_t *pHaptics)
{
    epwmAppPwmCfg_t *pCfg = &pPwm->pwmCfg;

    /* Disable all the sub-modules by default */
    pPwm->enableDeadband = pHaptics->enableDeadband;
    pPwm->enableChopper = pHaptics->enableDeadband;
    pPwm->enableTripZone = pHaptics->enableDeadband;
    pPwm->enableEventTrigger = pHaptics->enableDeadband;
    pPwm->enableHighResolution = pHaptics->enableDeadband;

    /* Tb period/freq has to be double the required pwm frequency. */
    pCfg->tbCfg.pwmtbCounterFreqPrd = pHaptics->pwmFreq * 2U;
    pCfg->tbCfg.tbClk = pHaptics->tbClk;

    /* Action Qualifier Action Values */
    /* Toggle output when counter is equal to period value. */
    pCfg->aqCfg.prdAction      = EPQM_AQ_ACTION_TOLLGE;
}

