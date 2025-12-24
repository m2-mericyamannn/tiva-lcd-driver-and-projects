#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include <stdio.h>
#include "lcd.h"

// ==================================
// ADC MODÜLÜ ARAYÜZÜ (PROJEYE UYUMLU)
// ==================================

// ADC0 + Sequencer3 baþlatýlýr (tek kanal, polling)
void ADC_Init(void);

// ADC'den tek örnek alýr ve sonucu döndürür
uint16_t ADC_Read(void);
// LCD üzerinde ADC volt deðerini gösterir
// row, col -> LCD baþlangýç konumu
void LCD_ADC_Goster(uint8_t row, uint8_t col);

extern uint16_t adc_raw;
extern float adc_voltage;

#endif // ADC_H
