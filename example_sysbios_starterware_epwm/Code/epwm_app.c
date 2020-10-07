/**
 * \file   epwm_app.c
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "types.h"
#include "chipdb.h"
#include "pinmux.h"
#include "epwm.h"
#include "error.h"
#include "console_utils.h"
#include "soc_control.h"

/* Application header files */
#include "epwm_app.h"
#include "prcm.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API configures the ePWM module
 *
 * \param   pObj             pointer to the ePwm object data structure.
 */
static void EpwmAppPwmCfg(epwmAppPwmObj_t *pObj);

/**
 * \brief   This API configures the Timebase Sub-module.
 *
 * \param   baseAddr           Base address of PWMSS instance used
 * \param   pwmFuncClk         PWM functional clock value in Hz
 * \param   epwmTimebaseCfg_t  Pointer to the Time base sub-module configuration
 *                             data structure
 */
static void EpwmAppTimebaseModuleCfg(uint32_t baseAddr,
                                     uint32_t pwmFuncClk,
                                     epwmTimebaseCfg_t *pTbCfg);

static int32_t EpwmAppSocInfoGet(epwmAppPwmObj_t *pObj);

static int32_t EPWMAppInit(epwmAppPwmObj_t *pPwm);

#define ECU_DEFAULT_CMP_VAL     (0x4000U)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** Motor 0 EPWM Configuration */
epwmAppPwmObj_t gstConfEpwm1aEcu0 =
{
    0U, /* pwmCh*/
    1U, /* instNum*/
    0U, /* instAddr*/
    100U * FREQ_MHZ, /* funcClk*/
    FALSE, /* enableDeadband */
    FALSE, /* enableChopper */
    FALSE, /* enableTripzone */
    FALSE, /* enableEventTrigger */
    FALSE, /* enableHighResolution */
    {
        {
            10U * FREQ_MHZ, /* tbClk */
            500U, /* pwmtbCounterFreqPrd */
            EPWM_TB_COUNTER_DIR_UP, /* tbCntrDirection */
            FALSE, /* enableSynchronization */
            0U, /* cntDirAfterSync */
            0U, /* phsCountAfterSync */
            0U  /* syncOutSrc */
        }, /* epwmTimebaseCfg_t */
        {
             ECU_DEFAULT_CMP_VAL, /* cmpAValue */
             ECU_DEFAULT_CMP_VAL  /* cmpBValue */
        }, /* epwmCounterCmpCfg_t */
        {
            EPWM_AQ_ACTION_DONOTHING, /* zeroAction */
            EPWM_AQ_ACTION_LOW, /* prdAction */
            EPWM_AQ_ACTION_HIGH, /* cmpAUpAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpADownAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpBUpAction */
            EPWM_AQ_ACTION_DONOTHING  /* cmpBDownAction */
        }, /* epwmAqActionCfg_t */
        {
            0U, /* inputMode */
            0U, /* outputMode */
            0U, /* polaritySelect */
            0U, /* risingEdgeDelay */
            0U  /* fallingEdgeDelay */
        }, /* epwmDeadbandCfg_t*/
        {
            0U, /* dutyCycle */
            0U, /* clkFrequency */
            0U  /* oneShotPulseWidth */
        }, /* epwmChopperCfg_t */
        {
            0U, /* tripAction */
            0U, /* tripEvtType */
            0U, /* tripPin */
            0U  /* enableTripIntr */
        }, /* epwmTripzoneCfg_t */
        {
            0U, /* intrEvtSource */
            0U  /* intrPrd */
        }  /* epwmEtCfg_t */
    } /* epwmAppPwmCfg_t*/
}; /* epwmAppPwmObj_t */


/** Motor 1 EPWM Configuration */
epwmAppPwmObj_t gstConfEpwm1bEcu1 =
{    
	1U, /* pwmCh*/
    1U, /* instNum*/
    0U, /* instAddr*/
    100U * FREQ_MHZ, /* funcClk*/
    FALSE, /* enableDeadband */
    FALSE, /* enableChopper */
    FALSE, /* enableTripzone */
    FALSE, /* enableEventTrigger */
    FALSE, /* enableHighResolution */
    {
        {
            10U * FREQ_MHZ, /* tbClk */
            500U, /* pwmtbCounterFreqPrd */
            EPWM_TB_COUNTER_DIR_UP, /* tbCntrDirection */
            FALSE, /* enableSynchronization */
            0U, /* cntDirAfterSync */
            0U, /* phsCountAfterSync */
            0U  /* syncOutSrc */
        }, /* epwmTimebaseCfg_t */
        {
             ECU_DEFAULT_CMP_VAL, /* cmpAValue */
             ECU_DEFAULT_CMP_VAL  /* cmpBValue */
        }, /* epwmCounterCmpCfg_t */
        {
            EPWM_AQ_ACTION_DONOTHING, /* zeroAction */
            EPWM_AQ_ACTION_LOW, 	  /* prdAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpAUpAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpADownAction */
            EPWM_AQ_ACTION_HIGH, 	  /* cmpBUpAction */
            EPWM_AQ_ACTION_DONOTHING  /* cmpBDownAction */
        }, /* epwmAqActionCfg_t */
        {
            0U, /* inputMode */
            0U, /* outputMode */
            0U, /* polaritySelect */
            0U, /* risingEdgeDelay */
            0U  /* fallingEdgeDelay */
        }, /* epwmDeadbandCfg_t*/
        {
            0U, /* dutyCycle */
            0U, /* clkFrequency */
            0U  /* oneShotPulseWidth */
        }, /* epwmChopperCfg_t */
        {
            0U, /* tripAction */
            0U, /* tripEvtType */
            0U, /* tripPin */
            0U  /* enableTripIntr */
        }, /* epwmTripzoneCfg_t */
        {
            0U, /* intrEvtSource */
            0U  /* intrPrd */
        }  /* epwmEtCfg_t */
    } /* epwmAppPwmCfg_t*/
}; /* epwmAppPwmObj_t */


/** Motor 2 EPWM Configuration */
epwmAppPwmObj_t gstConfEpwm2aEcu2 =
{
    0U, /* pwmCh*/
    2U, /* instNum*/
    0U, /* instAddr*/
    100U * FREQ_MHZ, /* funcClk*/
    FALSE, /* enableDeadband */
    FALSE, /* enableChopper */
    FALSE, /* enableTripzone */
    FALSE, /* enableEventTrigger */
    FALSE, /* enableHighResolution */
    {
        {
            10U * FREQ_MHZ, /* tbClk */
            500U, /* pwmtbCounterFreqPrd */
            EPWM_TB_COUNTER_DIR_UP, /* tbCntrDirection */
            FALSE, /* enableSynchronization */
            0U, /* cntDirAfterSync */
            0U, /* phsCountAfterSync */
            0U  /* syncOutSrc */
        }, /* epwmTimebaseCfg_t */
        {
             ECU_DEFAULT_CMP_VAL, /* cmpAValue */
             ECU_DEFAULT_CMP_VAL  /* cmpBValue */
        }, /* epwmCounterCmpCfg_t */
        {
            EPWM_AQ_ACTION_DONOTHING, /* zeroAction */
            EPWM_AQ_ACTION_LOW, /* prdAction */
            EPWM_AQ_ACTION_HIGH, /* cmpAUpAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpADownAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpBUpAction */
            EPWM_AQ_ACTION_DONOTHING  /* cmpBDownAction */
        }, /* epwmAqActionCfg_t */
        {
            0U, /* inputMode */
            0U, /* outputMode */
            0U, /* polaritySelect */
            0U, /* risingEdgeDelay */
            0U  /* fallingEdgeDelay */
        }, /* epwmDeadbandCfg_t*/
        {
            0U, /* dutyCycle */
            0U, /* clkFrequency */
            0U  /* oneShotPulseWidth */
        }, /* epwmChopperCfg_t */
        {
            0U, /* tripAction */
            0U, /* tripEvtType */
            0U, /* tripPin */
            0U  /* enableTripIntr */
        }, /* epwmTripzoneCfg_t */
        {
            0U, /* intrEvtSource */
            0U  /* intrPrd */
        }  /* epwmEtCfg_t */
    } /* epwmAppPwmCfg_t*/
}; /* epwmAppPwmObj_t */


/** Motor 3 EPWM Configuration */
epwmAppPwmObj_t gstConfEpwm2bEcu3 =
{    
	1U, /* pwmCh*/
    2U, /* instNum*/
    0U, /* instAddr*/
    100U * FREQ_MHZ, /* funcClk*/
    FALSE, /* enableDeadband */
    FALSE, /* enableChopper */
    FALSE, /* enableTripzone */
    FALSE, /* enableEventTrigger */
    FALSE, /* enableHighResolution */
    {
        {
            10U * FREQ_MHZ, /* tbClk */
            500U, /* pwmtbCounterFreqPrd */
            EPWM_TB_COUNTER_DIR_UP, /* tbCntrDirection */
            FALSE, /* enableSynchronization */
            0U, /* cntDirAfterSync */
            0U, /* phsCountAfterSync */
            0U  /* syncOutSrc */
        }, /* epwmTimebaseCfg_t */
        {
             ECU_DEFAULT_CMP_VAL, /* cmpAValue */
             ECU_DEFAULT_CMP_VAL  /* cmpBValue */
        }, /* epwmCounterCmpCfg_t */
        {
            EPWM_AQ_ACTION_DONOTHING, /* zeroAction */
            EPWM_AQ_ACTION_LOW, 	  /* prdAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpAUpAction */
            EPWM_AQ_ACTION_DONOTHING, /* cmpADownAction */
            EPWM_AQ_ACTION_HIGH, 	  /* cmpBUpAction */
            EPWM_AQ_ACTION_DONOTHING  /* cmpBDownAction */
        }, /* epwmAqActionCfg_t */
        {
            0U, /* inputMode */
            0U, /* outputMode */
            0U, /* polaritySelect */
            0U, /* risingEdgeDelay */
            0U  /* fallingEdgeDelay */
        }, /* epwmDeadbandCfg_t*/
        {
            0U, /* dutyCycle */
            0U, /* clkFrequency */
            0U  /* oneShotPulseWidth */
        }, /* epwmChopperCfg_t */
        {
            0U, /* tripAction */
            0U, /* tripEvtType */
            0U, /* tripPin */
            0U  /* enableTripIntr */
        }, /* epwmTripzoneCfg_t */
        {
            0U, /* intrEvtSource */
            0U  /* intrPrd */
        }  /* epwmEtCfg_t */
    } /* epwmAppPwmCfg_t*/
}; /* epwmAppPwmObj_t */


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t InitECU(void)
{
	 int32_t status = S_PASS;
	 
	 status = EPWMAppInit(&gstConfEpwm1aEcu0);
	 
	 if(status == S_PASS)
	 {
		 status |= EPWMAppInit(&gstConfEpwm1bEcu1);
	 }
	 
	 if(status == S_PASS)
	 {
		 status |= EPWMAppInit(&gstConfEpwm2aEcu2);
	 }
	 
	 if(status == S_PASS)
	 {
		 status |= EPWMAppInit(&gstConfEpwm2bEcu3);
	 }
	 
	 return status;
	 
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t EPWMAppInit(epwmAppPwmObj_t *pPwm)
{
    int32_t status = S_PASS;
	
	/* Get the base address of the Module */	
	status = EpwmAppSocInfoGet(pPwm);
	if(S_PASS == status)
	{		
		/* Enable clocks for EPWM module inside the PWM sub system. */
		EHRPWMClockEnable(pPwm->instAddr);

		/* Enable Time base clock for PWMSS module */
		SOCCtrlPwmssTimebaseClkEnable(pPwm->instNum);

		/* EPWM channel configuration */
		EpwmAppPwmCfg(pPwm);
	}

    return status;
}

static void EpwmAppPwmCfg(epwmAppPwmObj_t *pObj)
{
    uint32_t baseAddr = pObj->instAddr;
    uint32_t pwmCh    = pObj->pwmCh;
    uint32_t pwmFuncClk = pObj->funcClk;
    epwmAppPwmCfg_t *pPwm = &pObj->pwmCfg;

    /* Configure the Time base Sub-Module */
    EpwmAppTimebaseModuleCfg(baseAddr, pwmFuncClk, &pPwm->tbCfg);

    /* Configure Action Qualifier */
    EPWMAqActionOnOutputCfg(baseAddr, pwmCh, &pPwm->aqCfg);
	
	/* Counter Comparator A configuration */
    EPWMCounterComparatorCfg(baseAddr, pwmCh, pPwm->ccCfg.cmpAValue,
                             EPWM_SHADOW_REG_CTRL_DISABLE, EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);


    /* Dead band sub-module configuration */
    if(TRUE == pObj->enableDeadband)
    {
       /* Enable and configure dead band sub module */
       EPWMDeadbandCfg(baseAddr, &pPwm->dbCfg);
    }
    else
    {
        /* Bypass dead band sub module */
        EPWMDeadbandBypass(baseAddr);
    }

  /* Chopper sub-module configuration */
    if(TRUE == pObj->enableChopper)
    {
        /* Configure chopper sub - module */
        EPWMChopperCfg(baseAddr, &pPwm->chpCfg);

        /* Enable Chopper */
        EPWMChopperEnable(baseAddr, TRUE);
    }
    else
    {
        /* Disable Chopper */
        EPWMChopperEnable(baseAddr, FALSE);
    }

  /* Trip Zone Sub-Module Configuration */
    if(TRUE == pObj->enableTripZone)
    {
        /* Configure the Trip action */
        EPWMTzTriggerTripAction(baseAddr, EPWM_TZ_TRIP_ACTION_HIGH, pwmCh);

        /* Enable the Trip event */
        EPWMTzTripEventEnable(baseAddr, pPwm->tzCfg.tripEvtType,
            pPwm->tzCfg.tripPin);
    }
    else
    {
        /* Disable trip zone event handling and ignore all trip zone events */
        EPWMTzTripEventDisable(baseAddr, EPWM_TZ_EVENT_ONE_SHOT,
            pPwm->tzCfg.tripPin);
        EPWMTzTripEventDisable(baseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE,
            pPwm->tzCfg.tripPin);
    }

  /* Event trigger sub - module configuration */
    if(TRUE == pObj->enableEventTrigger)
    {
        /* Configure the Event trigger processing */
        EPWMEtIntrCfg(baseAddr, pPwm->etCfg.intrEvtSource, pPwm->etCfg.intrPrd);
    }
    else
    {
        /* Disable Event trigger interrupts */
        EPWMEtIntrDisable(baseAddr);
    }

    /**
     * High resolution feature is supported only on PWM A channel. If channel
     * is A then proceed with High Resolution processing.
     */
    if(EPWM_OUTPUT_CH_A == pwmCh)
    {
        if(TRUE == pObj->enableHighResolution)
        {
            /* configure high resolution feature */
            EHRPWMConfigHR(baseAddr, pPwm->hrCfg.delayBusSelect,
                pPwm->hrCfg.delayMode);

            if(EPWM_HR_DELAY_BUS_SEL_CMPAHR == pPwm->hrCfg.delayBusSelect)
            {
                /* Load comparator A High-resolution counter value */
                EPWMHrLoadCmpAHrValue(baseAddr, pPwm->hrCfg.cmpAHighResVal,
                    EPWM_HR_REG_ACT_LOAD_CNT_ZRO_PULSE);
            }
            else  /* EPWM_HR_DELAY_BUS_SEL_TBPHSHR */
            {
                /* Load Timebase phase high resolution value */
                EHRPWMLoadTBPHSHR(baseAddr,
                    pPwm->hrCfg.tbPhaseHighResVal);
            }
        }
        else
        {
            /* Disable High Resolution Feature */
            EHRPWMHRDisable(baseAddr);
        }
    }	
}


static void EpwmAppTimebaseModuleCfg(uint32_t baseAddr,
                                     uint32_t pwmFuncClk,
                                     epwmTimebaseCfg_t *pTbCfg)
{
    /* Configure Time base clock */
    EHRPWMTimebaseClkConfig(baseAddr, pTbCfg->tbClk, pwmFuncClk);

    /* Configure PWM time base counter frequency and direction */
    EPWMTbPwmFreqCfg(baseAddr, pTbCfg->tbClk,
        pTbCfg->pwmtbCounterFreqPrd, pTbCfg->tbCntrDirection,
        EPWM_SHADOW_REG_CTRL_DISABLE);

    if(TRUE == pTbCfg->enableSynchronization)
    {
        /* Enable Synchronization */
        EPWMTbSyncEnable(baseAddr, pTbCfg->phsCountAfterSync,
            pTbCfg->cntDirAfterSync);
    }
    else
    {
        /* Disable Synchronization */
        EHRPWMTimebaseSyncDisable(baseAddr);
    }

    /* Configure Sync out signal */
    EPWMTbSetSyncOutMode(baseAddr, pTbCfg->syncOutSrc);

    /* Configure the emulation behaviour */
    EPWMTbSetEmulationMode(baseAddr, EPWM_TB_EMU_MODE_STP_AFT_NEXT_CYCLE);
}

static int32_t EpwmAppSocInfoGet(epwmAppPwmObj_t *pObj)
{
    int32_t status = S_PASS;

    /* Get the base address of the Module */
    if(TRUE == CHIPDBIsResourcePresent(CHIPDB_MOD_ID_PWMSS, pObj->instNum))
    {
        pObj->instAddr = CHIPDBBaseAddress(CHIPDB_MOD_ID_PWMSS, pObj->instNum);
    }
    else
    {
       //UART_printf("PWMSS instance number is not present!\n");
       status = E_FAIL;
    }

    return status;
}

