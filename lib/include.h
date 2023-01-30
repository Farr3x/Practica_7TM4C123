
#ifndef LIB_INCLUDE_H_
#define LIB_INCLUDE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _40MHZ 9
#define _20MHZ 19
#define _10MHZ 39
#define _50MHZ 0x07
#define _25MHZ 0x0F
#define _80MHZ 0x04 

#define F100HZ (20000000/100)

#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

#include "TM4C123GH6PM.h"
#include "GPIO.h"
#include "PLL.h"
#include "UART.h"
#include "ADC.h"

#endif /* INCLUDE_H_ */