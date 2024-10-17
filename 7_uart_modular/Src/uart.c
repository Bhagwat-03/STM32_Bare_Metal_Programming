
#include <uart.h>


#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)
#define CR1_TE 	(1U<<3)
#define CR1_UE  (1U<<13)
#define SR_TXE  (1U<<7)


#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ




#define UART_BAUDRATE 115200


static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate);
void uart_tx_init(void);
void uart2_write(int ch);

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void uart_tx_init(void){
//	Enable the clock to GPIOA

	RCC->AHB1ENR |= GPIOAEN;

	  GPIOA->MODER |= (1U<<5);
	  GPIOA->MODER &= ~(1U<<4);
	  GPIOA->AFR[0] |= (1U<<8);
	  GPIOA->AFR[0] |= (1U<<9);
	  GPIOA->AFR[0] |= (1U<<10);
	  GPIOA->AFR[0] &= ~(1U<<11);


	  RCC->APB1ENR |= UART2EN;

//	  Configure Baudrate
	  uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

//	  Configure Transfer Direction
 	  USART2->CR1 = CR1_TE; //Everything else in the register will be 0 and sets the pin 3 to 1

//	  Set the Word Length
	  USART2->CR1 |= CR1_UE; //Enabling the UART

}
static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate){
	USARTx ->BRR = compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate){
	return ((PeriphClk +(BaudRate/2U))/BaudRate);
}


void uart2_write(int ch){
//	Make sure the transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}

//	Write to transmit data register
	USART2->DR = (ch & 0xFF);

}
