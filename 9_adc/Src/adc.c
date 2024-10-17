#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN (1U << 1)
#define ADC_ENR (1U << 8)
#define ADR_ON (1U << 0)
#define SW_ST (1U << 30)
#define SR_EOC (1U << 1)
#define CR2_CONT (1U << 1)

void adc_converter(void) {
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |= (1U << 2) | (1U << 3); // Set PA1 as analog mode
    RCC->APB2ENR |= ADC_ENR;               // Enable ADC clock

    ADC1->SQR3 = 0;  // Set ADC channel 0 (adjust as per your required channel)
    ADC1->CR2 = ADR_ON;  // Power on the ADC
}

void start_conversion(void) {
    ADC1->CR2 |= SW_ST; // Start conversion with software trigger
}

uint32_t adc_read() {
    while (!(ADC1->SR & SR_EOC)) { /* Wait for end of conversion */ }
    return ADC1->DR;
}
