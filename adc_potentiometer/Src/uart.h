#ifndef UART_H_
#define UART_H_

void uart_en(void);
void uart_write(char ch);
char uart_read(void);
void uart_write_str(char *str);

#endif
