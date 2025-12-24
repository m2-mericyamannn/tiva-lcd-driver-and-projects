#include "uart.h"
#include <stdio.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

// ===== Dýþarýdan gelen saat deðiþkenleri =====
extern volatile uint8_t saat, dakika, saniye;

// ===== RX Parser Deðiþkenleri =====
static char lcd_temp_buf[4];
static uint8_t lcd_idx = 0;
static bool veri_aliyor = false;

static char time_buf[12];
static uint8_t time_i = 0;
static bool time_mode = false;
static volatile bool text_ready = false;
static char text_buf[4];
// ============================
// UART DONANIM INIT
// ============================
void UART_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(
        UART0_BASE,
        SysCtlClockGet(),
        115200,
        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE
    );

    UARTEnable(UART0_BASE);
}

// ============================
// UART RX PROCESS
// ============================
void UART_ProcessRX(void)
{
    while (UARTCharsAvail(UART0_BASE))
    {
        char c = UARTCharGet(UART0_BASE);
        UARTCharPut(UART0_BASE, c); // echo

        // <ABC> LCD üst satýr
        if (c == '<')
        {
            veri_aliyor = true;
            lcd_idx = 0;
            //  DÝÐER MODLARI KAPAT
            time_mode = false;
            time_i = 0;


            continue;
        }

        if (veri_aliyor)
        {
            if (c == '>')
            {
                veri_aliyor = false;
                lcd_temp_buf[lcd_idx] = '\0';
                text_buf[0] = lcd_temp_buf[0];
                text_buf[1] = lcd_temp_buf[1];
                text_buf[2] = lcd_temp_buf[2];
                text_buf[3] = '\0';

                text_ready = true;

                continue;
            }

            if (lcd_idx < 3)
                lcd_temp_buf[lcd_idx++] = c;

            continue;
        }

        // !12:34:56 saat ayarý
        if (c == '!')
        {
            time_mode = true;
            time_i = 0;
            //  DÝÐER MODU KAPAT
            veri_aliyor = false;
            lcd_idx = 0;

            continue;
        }

        if (time_mode)
        {
            if (c == '\r' || c == '\n')
            {
                time_buf[time_i] = '\0';
                time_mode = false;

                int h, m, s;
                if (sscanf(time_buf, "%d:%d:%d", &h, &m, &s) == 3)
                {
                    if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60)
                    {
                        Timer_SetTime((uint8_t)h, (uint8_t)m, (uint8_t)s);
                    }
                }
                continue;
            }

            if (time_i < sizeof(time_buf) - 1)
                time_buf[time_i++] = c;
        }
    }
}

// ============================
// UART TX
// ============================
void UART_SendLine(const char *s)
{
    while(*s)
        UARTCharPut(UART0_BASE, *s++);

    UARTCharPut(UART0_BASE, '\r');
    UARTCharPut(UART0_BASE, '\n');
}

void UART_SendADC(uint32_t adc)
{
    char buf[20];
    sprintf(buf, "*%u", (unsigned int)adc);
    UART_SendLine(buf);
}

void UART_SendTime(uint8_t h, uint8_t m, uint8_t s)
{
    char buf[20];
    sprintf(buf, "#%02u:%02u:%02u", h, m, s);
    UART_SendLine(buf);
}
bool UART_TextReady(void)
{
    return text_ready;
}

void UART_GetText(char out[4])
{
    out[0]=text_buf[0];
    out[1]=text_buf[1];
    out[2]=text_buf[2];
    out[3]='\0';
    text_ready = false;
}
void UART_SendButton1(void)
{
    UARTCharPut(UART0_BASE, 'B');
    UARTCharPut(UART0_BASE, '1');
    UARTCharPut(UART0_BASE, '\r');
    UARTCharPut(UART0_BASE, '\n');
}
