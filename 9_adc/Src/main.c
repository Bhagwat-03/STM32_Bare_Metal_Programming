#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "uart.h"
#include "stm32f4xx.h"

#define GPIOAEN (1U<<0)
#define GPIOA_5 (1U<<5)

#define LED_PIN GPIOA_5

uint32_t value ;

int main(void){
	uart_rxtx_init();
	adc_converter();
	start_conversion();
	while(1){



		value = adc_read();
		printf("The value of the sensor is %d",(int)value);
	}
}
