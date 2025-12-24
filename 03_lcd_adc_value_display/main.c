#include "stdint.h"
#include "stdbool.h"
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "lcd.h"
#include "timer.h"
#include "adc.h"

void Tiva_init()
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,
                     GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);

}
uint16_t adc_val;
char adc_buf[6];
float volt;

int main(void)
{
    Tiva_init();
    LCD_init();
    LCD_clear();
    Timer0_Init();
    ADC_Init();

    LCD_setcursorPosition(1, 1);
    LCD_print("m2-Mericyamannn*");


    while(1)
    {
        LCD_SaatGoster();
        SysCtlDelay(SysCtlClockGet() / 3 / 20); // ~50 ms

        LCD_ADC_Goster(2, 10);
        SysCtlDelay(SysCtlClockGet() / 3 / 20); // ~50 ms


        // Ana döngü – ileride güncellenecek
    }
}
