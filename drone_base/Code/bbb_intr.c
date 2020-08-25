/*
 * bbb_intr.c
 *
 *  Created on: 2020. 7. 17.
 *      Author: AWT
 */

volatile int irq_from_device = 0;

int giIntrTest = 0;

void icm20948_GPIOIsr(void)
{
	giIntrTest++;

	if(giIntrTest == 1000000)
	{
		giIntrTest=0;
	}
    /* Check the Interrupt Status of the GPIO Card Detect pin. */
    irq_from_device = 1;
}



