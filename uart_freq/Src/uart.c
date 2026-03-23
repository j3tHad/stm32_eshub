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


void uart_pin_en(void) {

// enable GPIO for PA2 and PA3
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
}


void usart_reg_en(void) {

	// enable USART2 on APB1 bus
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN_Msk;

//	USART_SR (status register)
	// dont need to do anything
	// this is usually stuff sent by hardware to user

//	USART_DR (data register)
	// where the data actually is (9 bits total)
	// dont need to set anything, only need to read and write messages later

//	USART_BRR (baud rate register)
	// set to 9600bps at f_pclk = 16MHz (internal default!!) and OVER8=0
	USART2->BRR |= (0x3 << USART_BRR_DIV_Fraction_Pos);
	USART2->BRR |= (0x68UL << USART_BRR_DIV_Mantissa_Pos);

//	USART_CR1 (control register)
	USART2->CR1 |= USART_CR1_RE_Msk;
	USART2->CR1 |= USART_CR1_TE_Msk;
	//	USART1->CR1 &= ~USART_CR1_PS_Msk; // even parity
	USART2->CR1 &= ~USART_CR1_PCE_Msk;	// disable parity
	USART2->CR1 &= ~USART_CR1_M_Msk;	// 8 data bits
	USART2->CR1 |= USART_CR1_UE_Msk;
}



void uart_write(char ch) {

	while (!(USART2->SR & USART_SR_TXE_Msk));

	USART2->DR = ((int) ch & 0xFF);
}

char uart_read(void) {

	// if data is received and ready to be read
	while (!(USART2->SR & USART_SR_RXNE_Msk));

	return (char) (USART2->DR & 0xFF);
}



void uart_write_str(char *str) {
	while (*str) {
		uart_write(*str++);
	}
}

void process_char(void) {
	char ch = uart_read();
	uart_write(ch);

	// reset index
	if (rx_index >= MAX_BUFFER_LEN - 1) {
		rx_index = 0;
	}

	// check for newline
	if (ch == '\n' || ch == '\r') {
		rx_buffer[rx_index] = '\0';
		uart_write_str("\n");

		check_keyword();

		rx_index = 0;

	} else {
		rx_buffer[rx_index++] = ch;
	}
}

void check_keyword(void) {

	char msg[50];

	if (strncmp(rx_buffer, "SET_FREQ", 8) == 0) {
		// parse the freq val, number after set freq
		int val = atoi(&rx_buffer[9]);
		curr_freq = val;

		sprintf(msg, "< OK: Frequency set to %d Hz >\r\n", curr_freq);
		uart_write_str(msg);

	} else if (strncmp(rx_buffer, "GET_STATUS", 10) == 0) {

		sprintf(msg, "< STATUS OK, FREQ=%d >\r\n", curr_freq);
		uart_write_str(msg);

	} else {
		uart_write_str("< ERROR: Unknown Command >\r\n");
	}


}

