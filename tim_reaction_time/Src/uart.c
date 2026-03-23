#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stm32f411xe.h"
#include "uart.h"

// for io stream
struct __FILE { int handle; };
FILE __stdout;
FILE __stdin;

#define MAX_BUFFER_LEN 50

char rx_buffer[MAX_BUFFER_LEN];
int rx_index = 0;
int curr_freq = 0;

void uart_init(void)
{
	/******* enable GPIO for PA2 and PA3 *******/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// enable PA2
	// set to alternate function mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);
	//Tx at AF07
	GPIOA->AFR[0] |= (0x7UL << GPIO_AFRL_AFSEL2_Pos);

	// enable PA3
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 7);
	//Rx at AF07
	GPIOA->AFR[0] |= (0x7UL << GPIO_AFRL_AFSEL3_Pos);



	/******** enable USART2 on APB1 bus ********/
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

//	USART_BRR (baud rate register)
	// set to 9600bps at f_pclk = 16MHz (internal default!!) and OVER8=0
	USART2->BRR |= (0x3 << USART_BRR_DIV_Fraction_Pos);
	USART2->BRR |= (0x68UL << USART_BRR_DIV_Mantissa_Pos);

//	USART_CR1 (control register)
	USART2->CR1 |= USART_CR1_RE;
	USART2->CR1 |= USART_CR1_TE;
	//	USART1->CR1 &= ~USART_CR1_PS_Msk; // even parity
	USART2->CR1 &= ~USART_CR1_PCE;	// disable parity
	USART2->CR1 &= ~USART_CR1_M;	// 8 data bits
	USART2->CR1 |= USART_CR1_UE;
}


void uart_write(char ch)
{
	while (!(USART2->SR & USART_SR_TXE));

	USART2->DR = ((int) ch & 0xFF);
}

char uart_read(void)
{
	// if data is received and ready to be read
	while (!(USART2->SR & USART_SR_RXNE));

	return (char) (USART2->DR & 0xFF);
}



void uart_write_str(char *str)
{
	while (*str) {
		uart_write(*str++);
	}
}
