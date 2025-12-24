#include "lcd.h"

// Gecikme süresi (clock'e baðlý olarak ayarlanabilir)
static long sure = 50000;

// ======================
// LCD INITIALIZATION
// ======================
void LCD_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, RS | RW | EN);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, D7 | D6 | D5 | D4);

    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, 0x00);
    SysCtlDelay(sure);    // >= 20 ms

    // 4-bit mode init sequence (HD44780)
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x20);
    writeCommand();
    SysCtlDelay(10000);
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x20);
    writeCommand();
    SysCtlDelay(10000);
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x20);
    writeCommand();
    SysCtlDelay(10000);
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x20);
    writeCommand();

    // Write DDRAM adress Code
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x80);
    writeCommand();

    SysCtlDelay(sure);

    // Display ON, Cursor OFF
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x00);
    writeCommand();

    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0xC0);// For "Cursor Blink On" Replace C with D
    writeCommand();

    SysCtlDelay(sure);

    // Clear Display
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x00);
    writeCommand();

    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x10);
    writeCommand();

    SysCtlDelay(sure);

    // Return the cursor to the home position
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x00);
    writeCommand();

    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x20);
    writeCommand();
}

// ======================
// WRÝTE COMMAND
// ======================
void writeCommand(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, EN);
    SysCtlDelay(10000);
    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, 0x00);
}

// ======================
// CURSOR POSITION
// ======================
void LCD_setcursorPosition(unsigned char row, unsigned char column)
{
    unsigned char adres;

    if(row == 1)
        adres = 0x80;
    else if(row == 2)
        adres = 0xC0;
    else
        return;

    adres += (column - 1);

    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, 0x00);
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, adres & 0xF0);
    writeCommand();
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, (adres << 4) & 0xF0);
    writeCommand();
}

// ======================
// CLEAR LCD
// ======================
void LCD_clear(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, 0x00);
    SysCtlDelay(sure);

    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x00);
    writeCommand();

    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, 0x10);
    writeCommand();
}

// ======================
// STRING WRITE
// ======================
void LCD_print(const char *s)
{
    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, RS);
    while(*s)
    {
        data(*s++);
    }
}

// ======================
// DATA WRITE (4-BIT)
// ======================
char data(char value)
{
    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, value & 0xF0);
    writeData();

    GPIOPinWrite(GPIO_PORTB_BASE, D7 | D6 | D5 | D4, (value << 4) & 0xF0);
    writeData();

    return value;
}

// ======================
// DATA ENABLE PULSE
// ======================
void writeData(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, RS | EN);
    SysCtlDelay(10000);
    GPIOPinWrite(GPIO_PORTE_BASE, RS | RW | EN, RS);
}
