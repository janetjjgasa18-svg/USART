#ifndef _USART_h
#define _USART_h

#include <stm32f10x.h>

void init_usart1(void);
void usart1_sendbyte(unsigned char c);
void usart1_sendstring(char s[]);
uint8_t usart1_receivebyte(void);
void init_usart1_pin(void);

#endif