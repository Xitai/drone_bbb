#include "hw_control_AM335x.h"
#include "soc_AM335x.h"
#include "ehrpwm.h"

#include "hw_cm_per.h"
#include "hw_types.h"
#include "hw_pwmss.h"
#include "hw_ehrpwm.h"

#define COMPA 						(0)
#define COMPB 						(1)

#define CLOCK_DIV_VAL                 (10)
#define SOC_EHRPWM_0_MODULE_FREQ      (100000000)
#define SOC_EHRPWM_1_MODULE_FREQ      (100000000)
#define SOC_EHRPWM_2_MODULE_FREQ      (100000000)

void PWMSSModuleClkConfig(unsigned int instanceNum)
{
    HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) |= 
                             CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & 
     CM_PER_L3S_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) |= 
                             CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & 
     CM_PER_L3_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL) |= 
                             CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL) & 
                               CM_PER_L3_INSTR_CLKCTRL_MODULEMODE) != 
                                   CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL) |= 
                             CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL) & 
        CM_PER_L3_CLKCTRL_MODULEMODE) != CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) |= 
                             CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & 
                              CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL) != 
                                CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) |= 
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & 
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL) != 
                               CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL) |= 
                             CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL) & 
      CM_PER_L4LS_CLKCTRL_MODULEMODE) != CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE);

    if(0 == instanceNum)
    {
        HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS0_CLKCTRL) |=
            CM_PER_EPWMSS0_CLKCTRL_MODULEMODE_ENABLE;

        while(CM_PER_EPWMSS0_CLKCTRL_MODULEMODE_ENABLE !=
              (HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS0_CLKCTRL) &
               CM_PER_EPWMSS0_CLKCTRL_MODULEMODE));

        while((CM_PER_EPWMSS0_CLKCTRL_IDLEST_FUNC <<
               CM_PER_EPWMSS0_CLKCTRL_IDLEST_SHIFT) !=
              (HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS0_CLKCTRL) &
               CM_PER_EPWMSS0_CLKCTRL_IDLEST));

    }
    else if(1 == instanceNum)
    {
        HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS1_CLKCTRL) |=
            CM_PER_EPWMSS1_CLKCTRL_MODULEMODE_ENABLE;

        while(CM_PER_EPWMSS1_CLKCTRL_MODULEMODE_ENABLE !=
              (HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS1_CLKCTRL) &
               CM_PER_EPWMSS1_CLKCTRL_MODULEMODE));

        while((CM_PER_EPWMSS1_CLKCTRL_IDLEST_FUNC <<
               CM_PER_EPWMSS1_CLKCTRL_IDLEST_SHIFT) !=
               (HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS1_CLKCTRL) &
               CM_PER_EPWMSS1_CLKCTRL_IDLEST));

    }
    else if(2 == instanceNum)
    {
        HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS2_CLKCTRL) |=
            CM_PER_EPWMSS2_CLKCTRL_MODULEMODE_ENABLE;

        while(CM_PER_EPWMSS2_CLKCTRL_MODULEMODE_ENABLE !=
              (HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS2_CLKCTRL) &
               CM_PER_EPWMSS2_CLKCTRL_MODULEMODE));

        while((CM_PER_EPWMSS2_CLKCTRL_IDLEST_FUNC <<
               CM_PER_EPWMSS2_CLKCTRL_IDLEST_SHIFT) !=
               (HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS2_CLKCTRL) &
                CM_PER_EPWMSS2_CLKCTRL_IDLEST));
    }
    else
    {

    }

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & 
            CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & 
            CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & 
           (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK | 
            CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & 
           (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK )));
    
}



/**
 * \brief   This function Enables TBCLK(Time Base Clock) for specific
 *          EPWM instance of pwmsubsystem.
 *
 * \param   instance  It is the instance number of EPWM of pwmsubsystem.
 *
 **/
void PWMSSTBClkEnable(unsigned int instance)
{
    switch(instance)
    {
    
         case 0:
               HWREG(SOC_CONTROL_REGS + CONTROL_PWMSS_CTRL) |=
                                             CONTROL_PWMSS_CTRL_PWMSS0_TBCLKEN;
               break;
 
         case 1:
               HWREG(SOC_CONTROL_REGS + CONTROL_PWMSS_CTRL) |=
                                             CONTROL_PWMSS_CTRL_PWMMS1_TBCLKEN;
               break;
  
         case 2:
               HWREG(SOC_CONTROL_REGS + CONTROL_PWMSS_CTRL) |=
                                             CONTROL_PWMSS_CTRL_PWMSS2_TBCLKEN;
               break;

         default:
         break;
    } 
}

int EHRPWMConfigure(unsigned int uiInstance, unsigned int uiModuleFreq, unsigned int uiClkDiv, 
					unsigned int uiMaxPeriod, unsigned int uiCompaVal, unsigned int uiCompbVal)
{
	unsigned int uiEpwmNum = SOC_EPWM_0_REGS;
	
	if(uiInstance == 0)
	{
		uiEpwmNum = SOC_EPWM_0_REGS;
	}
	else if(uiInstance == 1)
	{
		uiEpwmNum = SOC_EPWM_1_REGS;
	}
	else if(uiInstance == 2)
	{
		uiEpwmNum = SOC_EPWM_2_REGS;
	}
	else
	{
		return -1;
	}
	
	if(uiMaxPeriod < 0)
	{
		uiMaxPeriod = 0;
	}
	else if(uiMaxPeriod > 0xFFFF)
	{
		uiMaxPeriod = 0xFFFF;
	}
	if(uiCompaVal < 0)
	{
		uiCompaVal = 0;
	}
	else if(uiCompaVal > 0xFFFF)
	{
		uiCompaVal = 0xFFFF;
	}
	if(uiCompbVal < 0)
	{
		uiCompbVal = 0;
	}
	else if(uiCompbVal > 0xFFFF)
	{
		uiCompbVal = 0xFFFF;
	}
	
    /* TimeBase configuration */
    /* Configure the clock frequency */
    EPWMTimebaseClkConfig(uiEpwmNum,
                            uiModuleFreq/uiClkDiv,
                            uiModuleFreq);

    /* Configure the period of the output waveform */
    EPWMPWMOpFreqSet(uiEpwmNum,
                       uiModuleFreq/uiClkDiv,
                       (unsigned int)(uiModuleFreq/uiClkDiv)/uiMaxPeriod,
                       (unsigned int)EHRPWM_COUNT_UP,
                       (bool)EHRPWM_SHADOW_WRITE_ENABLE);

    /* Disable synchronization*/
    EPWMTimebaseSyncDisable(uiEpwmNum);

    /* Disable syncout*/
    EPWMSyncOutModeSet(uiEpwmNum, EHRPWM_SYNCOUT_DISABLE);

    /* Configure the emulation behaviour*/
    EPWMTBEmulationModeSet(uiEpwmNum, EHRPWM_STOP_AFTER_NEXT_TB_INCREMENT);

    /* Configure Counter compare cub-module */
   /* Load Compare A value */
    EHRPWMLoadCMPA(uiEpwmNum,
                   uiCompaVal,
                   (bool)EHRPWM_SHADOW_WRITE_ENABLE,
                   (unsigned int)EHRPWM_COMPA_LOAD_COUNT_EQUAL_ZERO,
                   (bool)EHRPWM_CMPCTL_OVERWR_SH_FL);

    /* Load Compare B value */
    EHRPWMLoadCMPB(uiEpwmNum,
                   uiCompbVal,
                   (bool)EHRPWM_SHADOW_WRITE_ENABLE,
                   (unsigned int) EHRPWM_COMPB_LOAD_COUNT_EQUAL_ZERO,
                   (bool)EHRPWM_CMPCTL_OVERWR_SH_FL);

    /* Configure Action qualifier */
	
	/* Toggle when CTR = CMPA */
    EHRPWMConfigureAQActionOnA(uiEpwmNum,
                               EHRPWM_AQCTLA_ZRO_DONOTHING,
                               EHRPWM_AQCTLA_PRD_EPWMXALOW,
                               EHRPWM_AQCTLA_CAU_EPWMXAHIGH,
                               EHRPWM_AQCTLA_CAD_DONOTHING,
                               EHRPWM_AQCTLA_CBU_DONOTHING,
                               EHRPWM_AQCTLA_CBD_DONOTHING,
                               EHRPWM_AQSFRC_ACTSFA_DONOTHING);
	
	
    /* Toggle when CTR = CMPB */
    EHRPWMConfigureAQActionOnB(uiEpwmNum,
                               EHRPWM_AQCTLB_ZRO_DONOTHING,
                               EHRPWM_AQCTLB_PRD_EPWMXBLOW,
                               EHRPWM_AQCTLB_CAU_DONOTHING,
                               EHRPWM_AQCTLB_CAD_DONOTHING,
                               EHRPWM_AQCTLB_CBU_EPWMXBHIGH,
                               EHRPWM_AQCTLB_CBD_DONOTHING,
                               EHRPWM_AQSFRC_ACTSFB_DONOTHING);

    /* Bypass dead band sub-module */
    EHRPWMDBOutput(uiEpwmNum, EHRPWM_DBCTL_OUT_MODE_BYPASS);

    /* Disable Chopper sub-module */
    EHRPWMChopperDisable(uiEpwmNum);

    /* Disable trip events */
    EHRPWMTZTripEventDisable(uiEpwmNum,(bool)EHRPWM_TZ_ONESHOT);
    EHRPWMTZTripEventDisable(uiEpwmNum,(bool)EHRPWM_TZ_CYCLEBYCYCLE);

    /* Event trigger */
    /* Generate interrupt every 3rd occurance of the event */
    EHRPWMETIntPrescale(uiEpwmNum, EHRPWM_ETPS_INTPRD_THIRDEVENT);
    /* Generate event when CTR = CMPB */
    EHRPWMETIntSourceSelect(uiEpwmNum, EHRPWM_ETSEL_INTSEL_TBCTREQUCMPBINC);

    /* Disable High resolution capability */
    EHRPWMHRDisable(uiEpwmNum);
	
	return 0;
}

int EHRPWMPeriodSetup(unsigned int uiInstance, unsigned int uiCOMPx, unsigned int uiPeriodVal)
{	
	unsigned int uiEpwmNum = SOC_EPWM_0_REGS,
				 uiCompNum = COMPA;
	
	
	if(uiInstance == 0)
	{
		uiEpwmNum = SOC_EPWM_0_REGS;
	}
	else if(uiInstance == 1)
	{
		uiEpwmNum = SOC_EPWM_1_REGS;
	}
	else if(uiInstance == 2)
	{
		uiEpwmNum = SOC_EPWM_2_REGS;
	}
	else
	{
		return -1;		
	}
	
	if(uiPeriodVal < 0)
	{
		uiPeriodVal = 0;
	}
	else if(uiPeriodVal > 0xFFFF)
	{
		uiPeriodVal = 0xFFFF;
	}
	
	if(uiCOMPx == 0)	// COMPA
	{
		HWREGH(uiEpwmNum + EHRPWM_CMPA) = uiPeriodVal & EHRPWM_CMPA_CMPA;
	}
	else if(uiCOMPx == 1) // COMPB
	{
		HWREGH(uiEpwmNum + EHRPWM_CMPB) = uiPeriodVal & EHRPWM_CMPB_CMPB;
	}
	else
	{
		return -1;
	}	
	
	return 0;
}

void PWMPinEnable(void)
{
	/* EHRPWM 0A */
	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_MCASP0_ACLKX) = CONTROL_CONF_MUXMODE(1); // bbb p9,31
		
	/* EHRPWM 0B */
	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_MCASP0_FSX) = CONTROL_CONF_MUXMODE(1); // bbb p9,29
	
	
	/* EHRPWM 1A */
	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_A(2)) = CONTROL_CONF_MUXMODE(6); // bbb p9,14
	
	/* EHRPWM 1B */
	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_A(3)) = CONTROL_CONF_MUXMODE(6); // bbb p9,16
	
	
	/* EHRPWM 2A */
	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(8)) = CONTROL_CONF_MUXMODE(4); // bbb p8 13
	
	/* EHRPWM 2B */
	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(9)) = CONTROL_CONF_MUXMODE(4); // bbb p8 19
}

void IntializePWM(void)
{
	PWMSSModuleClkConfig(0);
	PWMSSModuleClkConfig(1);
	PWMSSModuleClkConfig(2);
		
	/* Enable Clock for EHRPWM in PWM sub system */
	EHRPWMClockEnable(SOC_PWMSS0_REGS);
	EHRPWMClockEnable(SOC_PWMSS1_REGS);
    EHRPWMClockEnable(SOC_PWMSS2_REGS);
	
	/* Enable Timer Base Module Clock in control module */
	PWMSSTBClkEnable(0);
	PWMSSTBClkEnable(1);
    PWMSSTBClkEnable(2);
	
	/* EHRPWM is configured to generate PWM waveform on EPWMBxB Pin*/
	
	
	(void)EHRPWMConfigure(0, SOC_EHRPWM_0_MODULE_FREQ, CLOCK_DIV_VAL, 50000,0,0);
	(void)EHRPWMConfigure(1, SOC_EHRPWM_0_MODULE_FREQ, CLOCK_DIV_VAL, 50000,0,0);
	(void)EHRPWMConfigure(2, SOC_EHRPWM_0_MODULE_FREQ, CLOCK_DIV_VAL, 50000,0,0);
}
