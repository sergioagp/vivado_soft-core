// Author: Sergio Pereira
// Date: 2021/05/09
// Brief: UART0 driver

#ifndef __PRINT_UART_H
#define __PRINT_UART_H
void config_uart0();
void print_uart0(const char *s);
void putchar_uart0(char character);

inline int __io_putchar(int ch) {
    putchar_uart0(ch);
    return 1;
}

#endif
