/*
 *  ======== main.c ========
 */


//########################## HEADERS ##################################
// System Headers
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

//#include <consoleUtils.h>

#include <stdbool.h>

///* UART Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/test/src/UART_board.h>


/*
 * User Headers
 */
#include "icm20948_bbb.h"
#include "bbb_uart.h"
#include "bbb_hw.h"
#include "bbb_i2c.h"
//#include "icm20948_system.h"
#include "EmbUtils/Message.h"
#include "bbb_epwm.h"


/* Test */
#include "Devices/SensorTypes.h"

/*
 *  ======== taskFxn ========
 */
struct inv_icm20948_serif gstIcm20948_serif; // ��ż���
int32_t giTestCount[3] = {0,0,0};
extern I2C_Handle      ghImuI2cHandle;
extern inv_icm20948_t icm_device;


#ifdef INV_MSG_ENABLE
static void msg_printer(int level, const char * str, va_list ap);
#endif

//static char achPrintOutBuf[256];

///********************* EPWM *************************/
///** \brief Structure holding haptics-motor use-case specific parameters. */
//typedef struct epwmAppHapticsCfg
//{
//    uint32_t tbClk;
//    /**< Time base clock (Prescaled clock for PWMSS functional clock) in Hz. */
//    uint32_t pwmFreq;
//    /**< PWM output frequency in Hz. */
//    uint32_t enableDeadband;
//    /**< Enable dead band sub-module processing. */
//    uint32_t enableChopper;
//    /**< Enable chopper sub-module processing. */
//    uint32_t enableTripZone;
//    /**< Enable Trip zone processing. */
//    uint32_t enableEventTrigger;
//    /**< Enable Event trigger. */
//    uint32_t enableHighResolution;
//    /**< Enable High resolution pwm feature. */
//}epwmAppHapticsCfg_t;
//
///** \brief Global object for the EPWM Haptics motor Use case data structure.  */
//static epwmAppHapticsCfg_t gHapticsCfg;
//
///** \brief Global object for the EPWM IP configuration data structure.  */
//static epwmAppPwmObj_t gPwmCfg;
//
//
//static void EpwmAppUpdateCfgParams(epwmAppPwmObj_t *pPwm,
//                                   epwmAppHapticsCfg_t *pHaptics)
//{
//    epwmAppPwmCfg_t *pCfg = &pPwm->pwmCfg;
//
//    /* Disable all the sub-modules by default */
//    pPwm->enableDeadband = pHaptics->enableDeadband;
//    pPwm->enableChopper = pHaptics->enableDeadband;
//    pPwm->enableTripZone = pHaptics->enableDeadband;
//    pPwm->enableEventTrigger = pHaptics->enableDeadband;
//    pPwm->enableHighResolution = pHaptics->enableDeadband;
//
//    /* Tb period/freq has to be double the required pwm frequency. */
//    pCfg->tbCfg.pwmtbCounterFreqPrd = pHaptics->pwmFreq * 2U;
//    pCfg->tbCfg.tbClk = pHaptics->tbClk;
//
//    /* Action Qualifier Action Values */
//    /* Toggle output when counter is equal to period value. */
//    pCfg->aqCfg.prdAction      = EPQM_AQ_ACTION_TOLLGE;
//}




Void taskMovement(UArg a0, UArg a1)
{
    int rc = 0;
#ifdef INV_MSG_ENABLE
    /* Setup message logging */
    INV_MSG_SETUP(INV_MSG_LEVEL_MAX, msg_printer);             // ����� �α� �޽��� ���� -- ����/����
#endif

#if (1)
    INV_MSG(INV_MSG_LEVEL_INFO, "###################################"); // �޽��� printf
    INV_MSG(INV_MSG_LEVEL_INFO, "#   ICM20948 example              #"); // �޽��� printf
    INV_MSG(INV_MSG_LEVEL_INFO, "###################################"); // �޽��� printf

	gstIcm20948_serif.context   = 0; /* no need */
	gstIcm20948_serif.read_reg  = idd_io_hal_read_reg;			// Read Register�� �Լ����
	gstIcm20948_serif.write_reg = idd_io_hal_write_reg;		// Write Register�� �Լ����
	gstIcm20948_serif.max_read  = 1024*16; /* maximum number of bytes allowed per serial read */
	gstIcm20948_serif.max_write = 1024*16; /* maximum number of bytes allowed per serial write */

	gstIcm20948_serif.is_spi 	= false;				// SPI ��Ź������ ����

	/*
	* Reset icm20948 driver states
	*/
	inv_icm20948_reset_states(&icm_device, &gstIcm20948_serif);	// icm_device ��ũ���� �ʱ�ȭ �� ��ġ ����

	inv_icm20948_register_aux_compass(&icm_device, INV_ICM20948_COMPASS_ID_AK09916, AK0991x_DEFAULT_I2C_ADDR);	// �ֺ���ġ �� Compass ��ġ ��� �� �ּ� ����

	/*
	* Setup the icm20948 device
	*/
	rc = icm20948_sensor_setup();			// IMU ��ġ Ȯ�� �� �ʱ�ȭ

	/*
	* Now that Icm20948 device was initialized, we can proceed with DMP image loading
	* This step is mandatory as DMP image are not store in non volatile memory
	*/
	rc += load_dmp3();						// DMP3 ��� �ε�
	
	check_rc(rc, "Error sensor_setup/DMP loading.");

	rc += userSelfTest(INV_SENSOR_TYPE_RAW_ACCELEROMETER);
    rc += userStartSensor(INV_SENSOR_TYPE_ORIENTATION);

    //uchImuStart = 0x1;
#endif
    /**************************** EPWM **************************/
//    gPwmCfg     = EPWMAPPPWMOBJ_DEFAULT;

//    int32_t status = S_PASS;

    //EpwmAppUpdateCfgParams(&gPwmCfg, &gHapticsCfg);
    //EPWMAppInit(&gPwmCfg);




	while(1)
	{
		//giTestCount[0]++;
		//System_printf("enter taskMovement()\n");

		//System_flush(); /* force SysMin output to console */
		
		//Task_sleep(1);

		if (irq_from_device == 1) {
            inv_icm20948_poll_sensor(&icm_device, (void *)0, build_sensor_event_data);      // UART ���� �޽����� ���� IMU�� FIFO ������ ����

//          __disable_irq();    // 2020-06-11
            irq_from_device = 0;
//          __enable_irq();     // 2020-06-11
            //System_printf("Ori[%02x] = %2.8f | %2.8f | %2.8f", gstImuEvent.data.orientation.accuracy_flag, gstImuEvent.data.orientation.x,
            //                                                                            gstImuEvent.data.orientation.y,gstImuEvent.data.orientation.z);
            //memset((void*)achPrintOutBuf, '\0', sizeof(achPrintOutBuf));
            //System_sprintf(achPrintOutBuf, "Ori[%02x] = %2.8f | %2.8f | %2.8f", gstImuEvent.data.orientation.accuracy_flag,
            //                                                             gstImuEvent.data.orientation.x,
            //                                                             gstImuEvent.data.orientation.y,
            //                                                             gstImuEvent.data.orientation.z);
            //INV_MSG(INV_MSG_LEVEL_DEBUG, achPrintOutBuf);
            INV_MSG(INV_MSG_LEVEL_DEBUG, "Ori[%02x] = %2.8f | %2.8f | %2.8f", gstImuEvent.data.orientation.accuracy_flag, gstImuEvent.data.orientation.x,
                                                                              gstImuEvent.data.orientation.y,gstImuEvent.data.orientation.z);

            //System_printf("enter taskCommMove()\n");
            //System_flush();
        }
	}

}
Void taskCommMove(UArg a0, UArg a1)
{
    //uint8_t uchBuffer = 0x0;
    //i2c_master_read_register(0x68, 0x00, 1, &uchBuffer);
    //int i;
	while(1)
	{
	    //if(uchImuStart == 0x1)
	    {
            giTestCount[1]++;

            System_printf("enter taskCommMove()\n");

            System_flush(); /* force SysMin output to console */

            Task_sleep(1);
	    }
	}
}
Void taskCommStreamData(UArg a0, UArg a1)
{
	while(1)
	{
	    //if(uchImuStart == 0x1)
	    {
            giTestCount[2]++;
            System_printf("enter taskCommStreamData()\n");

            System_flush(); /* force SysMin output to console */

            Task_sleep(1);
	    }
	}
}

 
 
Void taskMain(UArg a0, UArg a1)
{
	Task_Handle task;
    Error_Block eb;
    int32_t status = S_PASS;

    System_printf("enter taskMain()\n");
	
    System_flush(); /* force SysMin output to console */
	
	
	//--------------------------
	// Device Initialize
	//
	// Board Init
	initBbbDevice();

	// GPIO
	initBbbGpio();
		
	// I2C
	//initBbbI2c();
	//Task_sleep(1);
	
	// Interrupt
	//ext_intr_init();				// ����� ���ͷ�Ʈ & pin ����
	
	// PWM
    status = InitECU();
    if(S_PASS == status)
    {
        //UART_printf("\nNow Initializing ECU ...\n");
    }
    else
    {
        //UART_printf("\nECU Initializing Fail...\n");
    }
	
	//--------------------------
	// Task Initialize
	//
    task = Task_create(taskMovement, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

	task = Task_create(taskCommMove, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }
	
	task = Task_create(taskCommStreamData, NULL, &eb);
	task = Task_create(uart_test, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
       BIOS_exit(0);
    }
}

/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;
    Error_Block eb;	

    Error_init(&eb);
    task = Task_create(taskMain, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }
	
    BIOS_start();    /* does not return */
    return(0);
}

#ifdef INV_MSG_ENABLE
/*
* Printer function for message facility
*/
static void msg_printer(int level, const char * str, va_list ap){

    static char out_str[256]; /* static to limit stack usage */
    unsigned idx = 0;
    const char * ptr = out_str;
    const char * s[INV_MSG_LEVEL_MAX] = {
        "",    // INV_MSG_LEVEL_OFF
        "[E] ", // INV_MSG_LEVEL_ERROR
        "[W] ", // INV_MSG_LEVEL_WARNING
        "[I] ", // INV_MSG_LEVEL_INFO
        "[V] ", // INV_MSG_LEVEL_VERBOSE
        "[D] ", // INV_MSG_LEVEL_DEBUG
    };
    idx += snprintf(&out_str[idx], sizeof(out_str) - idx, "%s", s[level]);
    if(idx >= (sizeof(out_str)))
        return;
    idx += vsnprintf(&out_str[idx], sizeof(out_str) - idx, str, ap);
    if(idx >= (sizeof(out_str)))
        return;
    idx += snprintf(&out_str[idx], sizeof(out_str) - idx, "\r\n");
    if(idx >= (sizeof(out_str)))
        return;

    while(*ptr != '\0') {
        UART_printf("%c", *ptr);
        //usart_serial_putchar(DEBUG_UART, *ptr);
        ++ptr;
    }
}
#endif
