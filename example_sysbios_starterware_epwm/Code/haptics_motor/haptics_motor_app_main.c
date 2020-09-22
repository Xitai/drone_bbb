/**
 * \file   haptics_motor_app_main.c
 *
 * \brief  Example application main source file, which configures the IP and
 *         executes the use-case. This application demonstrates the use of
 *         EPWM to rotate the haptics motor.
 *
 *         Application Use-case:
 *         1. PWM output will be generated with 50% duty cycle.
 *         2. Haptics motor will be driven by this PWM output.
 *
 *         Running the example:
 *         1. Load the example application on the target and run.
 *         2. When the application is executed haptics motor will rotate.
 *
 *  \copyright Copyright (C) 2013 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

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
