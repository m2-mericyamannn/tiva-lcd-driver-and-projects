#ifndef UART_APP_H
#define UART_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"

// ============================
// UART ARAYÜZ FONKSÝYONLARI
// ============================

// UART0 donaným baþlatma
void UART_Init(void);

// PC'den gelen verileri iþle (<ABC>, !SAAT)
void UART_ProcessRX(void);

// PC'ye satýr gönder (\r\n ile)
void UART_SendLine(const char *s);

// UART üzerinden periyodik veri gönder
void UART_SendADC(uint32_t adc);
void UART_SendTime(uint8_t h, uint8_t m, uint8_t s);
bool UART_TextReady(void);
void UART_GetText(char out[4]);
void UART_SendButton1(void);

#endif
