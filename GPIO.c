#include "GPIO.h"

void GPIO_PC13_Init(void)
{
	RCC->APB2ENR |=(1U << 4);
	
	GPIOC->CRH &= ~(0XFU << 20);
	GPIOC->CRH |= (0X2U << 20);
}
void GPIO_PC13_On(void)
{
		GPIOC->BRR = (1U << 13);
}
	
void GPIO_PC13_Off(void)
{
	GPIOC->BSRR = (1U << 13);
}