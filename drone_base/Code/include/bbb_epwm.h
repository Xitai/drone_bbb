/**
 *  \file  epwm_app.h
 *
 */

#ifndef EPWM_APP_H_
#define EPWM_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "epwm.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Structure holding the EPWM configuration parameters. */
typedef struct epwmAppPwmCfg
{
    epwmTimebaseCfg_t tbCfg;
    /**< Timebase Sub-module configuration data structure. */
    epwmCounterCmpCfg_t ccCfg;
    /**< Counter comparator values . */
    epwmAqActionCfg_t aqCfg;
    /**< Action Qualifier Sub-module configuration data structure. */
    epwmDeadbandCfg_t dbCfg;
    /**< Dead band Sub-module configuration data structure. */
    epwmChopperCfg_t chpCfg;
    /**< Chopper sub-module configuration data structure. */
    epwmTripzoneCfg_t tzCfg;
    /**< Trip-zone sub-module configuration data structure. */
    epwmEtCfg_t etCfg;
    /**< Event Trigger sub-module configuration data structure. */
    epwmHighResolutionCfg_t hrCfg;
    /**< High Resolution sub-module configuration data structure. */
}epwmAppPwmCfg_t;


/**< \brief Structure holding the EPWM object data structure. */
typedef struct epwmAppPwmObj
{
    uint32_t pwmCh;
    /**< EPWM channel [A or B]. */
    uint32_t instNum;
    /**< EPWM instance number. */
    uint32_t instAddr;
    /**< EPWM instance address. */
    uint32_t funcClk;
    /**< Functional clock(in Hz) input to the PWMSS. */
    uint32_t enableDeadband;
    /**< Enable dead band sub-module processing. */
    uint32_t enableChopper;
    /**< Enable chopper sub-module processing. */
    uint32_t enableTripZone;
    /**< Enable Trip zone processing. */
    uint32_t enableEventTrigger;
    /**< Enable Event trigger. */
    uint32_t enableHighResolution;
    /**< Enable High resolution pwm feature. */
    epwmAppPwmCfg_t pwmCfg;
    /**< EPWM configuration data structure. */
}epwmAppPwmObj_t;


/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

extern epwmAppPwmObj_t gstConfEcu0;
extern epwmAppPwmObj_t gstConfEcu1;
extern epwmAppPwmObj_t gstConfEcu2;
extern epwmAppPwmObj_t gstConfEcu3;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t InitECU(void);
void EpwmCounterChange(epwmAppPwmObj_t *pObj, uint32_t uiCmpValue);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef EPWM_APP_H_ */
