
#ifndef __USART_H__
#define __USART_H__

#include "main.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define UART_BUFFER_SIZE 256 // Adjust as needed

extern UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void);
void hal_uart_printf(const char *format, ...);
#endif /* __USART_H__ */
