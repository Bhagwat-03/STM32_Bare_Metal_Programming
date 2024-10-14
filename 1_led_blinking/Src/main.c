//LED Blinking
// Port : A
// Pin : 5
#include <stdint.h>
#define PERIPH_BASE 					(0x40000000UL)
#define AHB1PERIPH_OFFSET 				(0x00020000UL)
#define AHB1PERIPH_BASE 				(PERIPH_BASE + AHB1PERIPH_OFFSET )
#define GPIOA_OFFSET  					(0x0U)
#define GPIOA_BASE 						(AHB1PERIPH_BASE + GPIOA_OFFSET )
#define RCC_OFFSET 						(0x3800UL)
#define RCC_BASE 						(AHB1PERIPH_BASE+ RCC_OFFSET )
#define AHB1EN_R_OFFSET 				(0x30UL)
#define RCC_AHB1EN_R 					(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET ))
#define GPIOAEN 						(1U<<0)   //The register will turn into  00000000000000000000000000000001
#define MODE_R_OFFSET 					(0x00UL)
#define GPIOA_MODE_R					(*(volatile unsigned int *)(GPIOA_BASE+MODE_R_OFFSET))
// (1u<<10)
// &=~(1U<<11)
#define ODR_OFFSET 						(0x14UL)
#define GPIOA_OD_R						(*(volatile unsigned int *)(GPIOA_BASE + ODR_OFFSET))
#define PIN5							(1U<<5)
#define LED_PIN 						PIN5

typedef struct{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;


#define RCC  ((RCC_TypeDef*)RCC_BASE)
#define GPIO ((GPIO_TypeDef*)GPIOA_BASE)

// rcc  ahb reg = 0b 0000 0000 0000 0000 1000 1111 0000 0000
// if we apply the equal sign then the other functions are also made 0 so we use the or Operator so only the first bit is 1 and others are not zeros this is called Friendly Programming
int main(){
//	1. Enable clock access to GPIOA
//	RCC_AHB1EN_R |= GPIOAEN ;
	RCC->AHB1ENR |= GPIOAEN;
//	2. Set PA5 to output pin
//
//	GPIOA_MODE_R |= (1u<<10);// Set bit 10 to Zero
//	GPIOA_MODE_R &=~(1U<<11);// Set bit 11 to Zero


	GPIO->MODER |= (1u<<10);
	GPIO->MODER &=~(1U<<11);
	while(1){
//		GPIOA_OD_R |= LED_PIN;


//		4. Experiment 2: Toggle PA5

//		GPIOA_OD_R ^= LED_PIN;
		GPIO->ODR ^= LED_PIN;
		for(int i=0;i<100000;i++){

		}
	}
}
