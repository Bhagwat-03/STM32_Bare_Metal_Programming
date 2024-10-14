
#include "stm32f4xx.h"


#define GPIOAEN 		(1U<<0)
#define GPIOCEN 		(1U<<2)

#define PIN5   			(1U<<5)
#define PIN13 			(1U<<13)


#define LED_PIN 		PIN5
#define BTN_PIN 		PIN13


void gpio_enable(){
	GPIOA->BSRR = LED_PIN;
}
void gpio_disable(){
	GPIOA->BSRR = (1U<<21);
}


int main(void){
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;
//	Here PA5 is set as the output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
//	Here we are setting PC13 as the input pin
	GPIOC ->MODER &= ~(1U<<26);
	GPIOC ->MODER &= ~(1U<<27);



	while(1){
		if(GPIOC->IDR & BTN_PIN){
			gpio_disable();
		}else{
			gpio_enable();
		}
	}
}
