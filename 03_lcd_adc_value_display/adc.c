#include "adc.h"



// ==================================
// ADC GLOBAL DEÐÝÞKENLERÝ
// ==================================
uint16_t adc_raw = 0;
float adc_voltage = 0.0f;

// ==================================
// ADC INIT
// PE4 -> ADC0 CH9 (Tiva-C)
// ==================================
void ADC_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4); // PE4

    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0,
                             ADC_CTL_CH9 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
}

// ==================================
// HAM ADC OKUMA (0–4095)
// ==================================
uint16_t ADC_ReadRaw(void)
{
    uint32_t adc_temp;   // <-- EKLENEN SATIR

    ADCProcessorTrigger(ADC0_BASE, 3);

    while(!ADCIntStatus(ADC0_BASE, 3, false));

    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, &adc_temp);  // <-- DEÐÝÞEN SATIR

    adc_raw = (uint16_t)(adc_temp & 0x0FFF);      // <-- 12-bit maskeleme
    return adc_raw;
}

// ==================================
// ADC VOLT OKUMA (0.00 – 3.30V)
// ==================================
float ADC_ReadVoltage(void)
{
    adc_raw = ADC_ReadRaw();
    adc_voltage = (adc_raw * 3.3f) / 4095.0f;
    return adc_voltage;
}

void LCD_ADC_Goster(uint8_t row, uint8_t col)
{
    char buf[6];
    uint16_t mv;

    ADC_ReadRaw();
    mv = (adc_raw * 3300UL) / 4095UL;

    // ---- SABÝT FORMAT: X.XXV ----
    buf[0] = (mv / 1000) + '0';
    buf[1] = '.';
    buf[2] = ((mv % 1000) / 100) + '0';
    buf[3] = ((mv % 100) / 10) + '0';
    buf[4] = 'V';
    buf[5] = '\0';


    // ---- SONRA GERÇEK DEÐERÝ YAZ ----
    LCD_setcursorPosition(row, col);
    LCD_print(buf);
}
