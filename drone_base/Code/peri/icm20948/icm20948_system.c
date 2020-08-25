#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <ti/drv/i2c/I2C.h>

#include "include/icm20948_system.h"
#include "include/Message.h"
//#include "consoleUtils.h"
/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/

/* I2C address of CAT24C256 e2prom */
#define  I2C_SLAVE_ADDR         (0x68)

/* Higher byte address (i.e A8-A15) */
#define  E2PROM_ADDR_MSB         0x00

/* Lower byte address (i.e A0-A7) */
#define  E2PROM_ADDR_LSB         0x00



/* BBB H/W Functions */
void icm20948_I2CIsr(void);
//void icm20948_SetupI2C(void);
//void I2CAINTCConfigure(void);
void I2C2ModuleClkConfig(void);
void imuPinMuxSetup(void);

//static void i2c_master_initialize(void);
//static unsigned long i2c_master_read_register(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, unsigned char *RegisterValue);
//static unsigned long i2c_master_write_register(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, const unsigned char *RegisterValue);


/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
/* BBB Variables */
volatile unsigned int tCount;
volatile unsigned int rCount;
volatile unsigned int flag = 1;
volatile unsigned int numOfBytes;
volatile unsigned char dataToSlave[2];
//volatile unsigned char dataToSlave;
volatile unsigned char dataFromSlave[50];


extern volatile int irq_from_device;

/*
* Variable for storing I2C Address
*/
uint8_t I2C_Address = ICM_I2C_ADDR_REVA;


/*!
* @brief	Sensor general interrupt handler, calls specific handlers.
*
* This function is called when an external interrupt is triggered by the sensor,
* checks interrupt registers of InvenSense Sensor to determine the source and type of interrupt
* and calls the specific interrupt handler accordingly.
*
* @param[in]	NULL
*
* @param[out]	NULL
*
* @return		NULL
*
*/
void ext_interrupt_handler(void)
{
	irq_from_device = 1;
}	

void switch_I2C_to_revA(void)
{
	I2C_Address = ICM_I2C_ADDR_REVA;
}

//InvScheduler 	scheduler;

//void hw_timer_start(uint32_t timer_freq){
////	uint32_t counts;
////	uint32_t ul_div;
////	uint32_t ul_tcclks;
////	uint32_t ul_sysclk = sysclk_get_cpu_hz();
////
////	NVIC_DisableIRQ(TC0_IRQn);
////	NVIC_ClearPendingIRQ(TC0_IRQn);
////	tc_find_mck_divisor((uint32_t)(timer_freq),		// The desired frequency as a uint32.
////		ul_sysclk,					// Master clock freq in Hz.
////		&ul_div,					// Pointer to register where divisor will be stored.
////		&ul_tcclks,					// Pointer to reg where clock selection number is stored.
////		ul_sysclk);					// Board clock freq in Hz.
////
////
////	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
////
////	/* Find the best estimate of counts, then write it to TC register C. */
////	counts = (ul_sysclk/ul_div)/timer_freq;
////
////	tc_write_rc(TC0, 0, counts);
////	tc_get_status(TC0, 0);
////	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
////	tc_start(TC0, 0);
////	NVIC_SetPriority(TC0_IRQn,0);
////	NVIC_EnableIRQ(TC0_IRQn);
//}

//void hw_timer_stop(void){
////	tc_stop(TC0, 0);
////	NVIC_DisableIRQ(TC0_IRQn);
////	NVIC_ClearPendingIRQ(TC0_IRQn);
//}

//static uint32_t Num50msTicks = 0;				// The timestamp timer ticks over every 50 ms.


//void TC0_Handler(void){
////	uint32_t ul_status;
////
////	ul_status = tc_get_status(TC0, 0);
////	ul_status &= tc_get_interrupt_mask(TC0, 0);
////
////	if (ul_status & TC_SR_CPCS)
////		Num50msTicks++;
//}

//volatile uint32_t ul_ticks = 0;

//void SysTick_Handler(void){
//	ul_ticks++;
//	//InvScheduler_updateTime(&scheduler);
//}


/******************************************************************************
**                      SYSTEM FUNCTIONS 
*******************************************************************************/

#ifdef INV_MSG_ENABLE
/*
* Printer function for message facility
*/
//static void msg_printer(int level, const char * str, va_list ap){
//
//	static char out_str[256]; /* static to limit stack usage */
//	unsigned idx = 0;
//	const char * ptr = out_str;
//	const char * s[INV_MSG_LEVEL_MAX] = {
//		"",    // INV_MSG_LEVEL_OFF
//		"[E] ", // INV_MSG_LEVEL_ERROR
//		"[W] ", // INV_MSG_LEVEL_WARNING
//		"[I] ", // INV_MSG_LEVEL_INFO
//		"[V] ", // INV_MSG_LEVEL_VERBOSE
//		"[D] ", // INV_MSG_LEVEL_DEBUG
//	};
//	idx += snprintf(&out_str[idx], sizeof(out_str) - idx, "%s", s[level]);
//	if(idx >= (sizeof(out_str)))
//		return;
//	idx += vsnprintf(&out_str[idx], sizeof(out_str) - idx, str, ap);
//	if(idx >= (sizeof(out_str)))
//		return;
//	idx += snprintf(&out_str[idx], sizeof(out_str) - idx, "\r\n");
//	if(idx >= (sizeof(out_str)))
//		return;
//
//	while(*ptr != '\0') {
//	    UART_printf(*ptr);
//		//ConsoleUtilsPrintf("%c", *ptr);
//		//usart_serial_putchar(DEBUG_UART, *ptr);
//		++ptr;
//	}
//}
#endif


//static uint32_t Num50msTicks = 0;				// The timestamp timer ticks over every 50 ms.

uint64_t inv_icm20948_get_time_us(void){
	return InvEMDFrontEnd_getTimestampUs();
}


uint64_t InvEMDFrontEnd_getTimestampUs(void){
//	uint32_t timer_counter_value = tc_read_cv(TC0, 0);		// Read the timer counter
//	uint32_t max_counter_value = tc_read_rc(TC0, 0);		// read the timer limit
//
//	// In order to get a micro-second timestamp, we track the number of 50 ms intervals since startup or rollover.
//	// This value is multiplied by the number of microseconds in 50 ms, and then add the number of microseconds since
//	// the last 50 ms tick.
//	// timer_counter_value / max_counter_value is the fraction of the current 50 ms interval that has already expired.
//	return (Num50msTicks * MICROSECONDS_PER_50ms) + ((timer_counter_value * MICROSECONDS_PER_50ms) / max_counter_value);

	return 0; // temp 2020-06-11
}

