#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#include "lcd.h"
#include "timer.h"

// ================================
// GLOBAL TIME VARIABLES
// ================================
volatile uint8_t saat   = 0;
volatile uint8_t dakika = 0;
volatile uint8_t saniye = 0;

static volatile bool lcd_guncelle = false;
static char saat_buffer[9]; // "SS:DD:SN"

// ================================
// TIMER0 ISR
// ================================
void Timer0_ISR(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    saniye++;
    if (saniye > 59)
    {
        saniye = 0;
        dakika++;
        if (dakika > 59)
        {
            dakika = 0;
            saat++;
            if (saat > 23)
                saat = 0;
        }
    }

    lcd_guncelle = true;
}

// ================================
// TIMER INITIALIZATION
// ================================
void Timer0_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));

    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()); // 1 saniye

    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0_ISR);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER0A);

    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);
}

// ================================
// LCD CLOCK UPDATE FUNCTION
// ================================
void LCD_SaatGoster(void)
{
    if (!lcd_guncelle)
        return;

    lcd_guncelle = false;

    sprintf(saat_buffer, "%02u:%02u:%02u",
            (unsigned int)saat,
            (unsigned int)dakika,
            (unsigned int)saniye);

    // LCD API'n ile UYUMLU
    LCD_setcursorPosition(2, 1);
    LCD_print(saat_buffer);
}

// ================================
// MANUAL TIME SET (OPTIONAL)
// ================================
void Timer_SetTime(uint8_t h, uint8_t m, uint8_t s)
{
    if (h < 24 && m < 60 && s < 60)
    {
        saat   = h;
        dakika = m;
        saniye = s;
        lcd_guncelle = true;
    }
}
