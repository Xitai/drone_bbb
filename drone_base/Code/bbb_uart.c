/*
 * bbb_uart.c
 *
 *  Created on: 2020. 7. 24.
 *      Author: AWT
 */

#ifndef CODE_BBB_UART_C_
#define CODE_BBB_UART_C_

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

/* UART Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>

#include <ti/drv/uart/test/src/UART_board.h>


 /* Length of the input in number of characters */
#define INPUT_LENGTH           (16U)

char echoPrompt[]="\nuart driver and utils example test cases :\nEnter 150 characters or press the esc \n";
char echoPrompt1[]="DATA RECEIVED IS\n ";



/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
//void padConfig_prcmEnable()
//{
//    /*Pad configurations */
//    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RXD,0x00040000);
//    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_UART1_TXD,0x00000000);
//
//}
Void uart_test(UArg arg0, UArg arg1)

{
    char input = '\n';
    char *buffPointer;

    buffPointer = (char*)malloc(INPUT_LENGTH);
    memset(buffPointer,0,INPUT_LENGTH);

    UART_puts("\nuart driver and utils example test cases :\nEnter 16 characters or press the esc \n",sizeof("uart driver and utils example test cases : please enter 16 characters or press the esc or carriage return\n"));

    while(1) {
        memset(buffPointer,0,INPUT_LENGTH);
        UART_gets(buffPointer, INPUT_LENGTH);
        UART_puts(&input,1);
        UART_printf("Data received is\n");
        UART_puts(buffPointer, INPUT_LENGTH);
        UART_printStatus("\nTest Passed\n");
        UART_puts("\nuart driver and utils example test cases :\nEnter 16 characters or press the esc \n",sizeof("uart driver and utils example test cases : please enter 16 characters or press the esc or carriage return\n"));
    }
} /* uart_test */

#endif /* CODE_BBB_UART_C_ */
