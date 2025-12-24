#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"


#include "lcd.h"

// ==================================
// TIMER / SAAT MODÜLÜ ARAYÜZÜ
// (main.c ve lcd.c ile uyumlu)
// ==================================

// Timer0'u 1 saniyelik zaman tabaný olacak þekilde baþlatýr
void Timer0_Init(void);

// LCD üzerinde anlýk saati (SS:DD:SN) formatýnda gösterir
// Bu fonksiyon main döngüsü (while(1)) içinde çaðrýlmalýdýr
void LCD_SaatGoster(void);

// Saati manuel olarak ayarlamak için
// Örnek: Timer_SetTime(12, 34, 56);
void Timer_SetTime(uint8_t saat, uint8_t dakika, uint8_t saniye);

#endif // TIMER_H
