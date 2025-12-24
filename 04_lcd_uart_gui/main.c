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
#include "uart.h"

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
static volatile bool sw1_event = false;

int main(void)
{
    Tiva_init();
    LCD_init();
    LCD_clear();
    Timer0_Init();
    ADC_Init();
    UART_Init();

    LCD_setcursorPosition(1, 1);
    LCD_print("m2-Mericyamannn*");

    char tmp[4];

    while(1)
    {
        UART_ProcessRX();
        LCD_SaatGoster();
        LCD_ADC_Goster(2, 10);

        static bool sw1_prev = true;
        bool sw1_now = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

        if (sw1_prev && !sw1_now)
        {
            SysCtlDelay(SysCtlClockGet() / 3 / 500); // ~2 ms debounce
            if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0)
            {
                sw1_event = true;   // 🔴 SADECE EVENT
            }
        }
        sw1_prev = sw1_now;


        // UART'tan gelen TEXT varsa LCD'ye yaz
        if (UART_TextReady())
        {
            SysCtlDelay(SysCtlClockGet() / 3 / 300); // ~1 ms

            UART_GetText(tmp);

            LCD_setcursorPosition(1,1);
            LCD_print("                ");
            LCD_setcursorPosition(1,1);
            LCD_print(tmp);
        }

        static uint32_t tx_cnt = 0;

        tx_cnt++;
        if (tx_cnt >= 20)   // ~1 saniye
        {
            tx_cnt = 0;

            // Önce buton olayı varsa gönder
            if (sw1_event)
            {
                UART_SendButton1();
                sw1_event = false;
            }

            // Sonra periyodik veriler
            UART_SendADC(adc_raw);
            UART_SendTime(saat, dakika, saniye);
        }

        // 6️⃣ KÜÇÜK delay (UART dostu)
        SysCtlDelay(SysCtlClockGet() / 3 / 200); // ~5 ms

    }
}
