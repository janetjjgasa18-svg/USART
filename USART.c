#include "USART.h"

void init_usart1(void){
	// Habilitar reloj para USART1, GPIOA y AFIO
	RCC->APB2ENR |= (1 << 14) | (1 << 2) | (1 << 0);
	
	// PA10 = RX1 input (Input Floating)
	GPIOA->CRH &= ~((1 << 11) | (1 << 10) | (1 << 9) | (1 << 8));
	GPIOA->CRH |= (1 << 10);
	
	// PA9 = TX1 output (Alternate Push-Pull, 50 MHz)
	GPIOA->CRH &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
	GPIOA->CRH |= (1 << 7) | (1 << 5) | (1 << 4);
	
	// Configurar USART1
	USART1->CR1 |= ((1 << 13) | (1 << 3) | (1 << 2)); // Enable USART, TX, RX
	USART1->BRR = 7500; // Baud rate 72,000,000 / 9,600 = 7,500
}

void usart1_sendbyte(unsigned char c){
	USART1->DR = c;
	while((USART1->SR & (1<<6)) == 0);
	USART1->SR &= ~(1<<6);
}

void usart1_sendstring(char s[]){
	int i = 0;
	while (i < 64) {
		if (s[i] == '\0') break;
		usart1_sendbyte(s[i++]);
	}
}

uint8_t usart1_receivebyte(void){
	while((USART1->SR & (1 << 5)) == 0);
	return USART1->DR;
}