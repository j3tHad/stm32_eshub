#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stm32f411xe.h"

void uart_pin_en(void);
void usart_reg_en(void);

void uart_write(char ch);
char uart_read(void);
void uart_write_str(char *str);

void process_char(void);
void check_keyword(void);
