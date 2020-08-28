/*
 * motorctl.h
 *
 *  Created on: 2020. 5. 22.
 *      Author: AWT
 */

#ifndef MOTORCTL_H_
#define MOTORCTL_H_


//void PWMSSModuleClkConfig(unsigned int instanceNum);
//void PWMSSTBClkEnable(unsigned int instance);
//int EHRPWMConfigure(unsigned int uiInstance, unsigned int uiModuleFreq, unsigned int uiClkDiv, unsigned int uiMaxPeriod,
//					unsigned int uiCompaVal, unsigned int uiCompbVal);
int EHRPWMPeriodSetup(unsigned int uiInstance, unsigned int uiCOMPx, unsigned int uiPeriodVal);
//void PWMPinEnable(void);
void IntializePWM(void);

#endif /* MOTORCTL_H_ */
