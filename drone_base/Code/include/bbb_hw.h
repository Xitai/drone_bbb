/*
 * bbb_hw.h
 *
 *  Created on: 2020. 7. 17.
 *      Author: AWT
 */

#ifndef CODE_INCLUDE_BBB_HW_H_
#define CODE_INCLUDE_BBB_HW_H_

bool initBbbDevice(void);
void initBbbGpio(void);

void configure_console(void);
void bbb_gpio_init(void);
void I2C2ModuleClkConfig(void);
void ext_intr_init(void);

#endif /* CODE_INCLUDE_BBB_HW_H_ */
