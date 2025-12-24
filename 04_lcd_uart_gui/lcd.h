#ifndef _LCD_H
#define _LCD_H
#include "stdint.h"
#include "stdbool.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

// ======================
// LCD PIN DEFINITIONS
// ======================
#define RS  GPIO_PIN_1
#define RW  GPIO_PIN_2
#define EN  GPIO_PIN_3

#define D4  GPIO_PIN_4
#define D5  GPIO_PIN_5
#define D6  GPIO_PIN_6
#define D7  GPIO_PIN_7

// ======================
// FUNCTION PROTOTYPES
// ======================
void LCD_init(void);
void writeCommand(void);
void LCD_clear(void);
void writeData(void);
void LCD_setcursorPosition(unsigned char row, unsigned char column);
char data(char value);
void LCD_print(const char *s);

#endif
