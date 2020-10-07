/*
 * bbb_system.h
 *
 *  Created on: 2020. 8. 14.
 *      Author: AWT
 */

#ifndef CODE_INCLUDE_BBB_SYSTEM_H_
#define CODE_INCLUDE_BBB_SYSTEM_H_

#include <xdc/std.h>

#define ECU_PASS	(0x0)
#define ECU_FAIL	(0x1)

typedef struct machine_status_set {
	uint32_t uiEcu;
	uint32_t uiImu;
} machine_status_t;

#endif /* CODE_INCLUDE_BBB_SYSTEM_H_ */
