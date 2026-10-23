#include "stm32f10x.h"
#include "USART.h"
#include "GPIO.h"   //[cite: 12]
#include "exti.h"   //[cite: 10]

uint32_t contador_pulsos = 0;

// Se eliminó Configurar_Sistema() para usar tus funciones GPIO_PC13_Init e init_exti

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR0)
    {
        contador_pulsos++;
        GPIOC->ODR ^= (1U << 13); // Alterna el estado del LED en PC13 (Toggle)
        EXTI->PR = EXTI_PR_PR0;   // Limpia la bandera
    }
}

// Envía un número por USART
void usart1_enviar_numero(uint32_t num)
{
    char buffer[12];
    int i = 0;
    if(num == 0)
    {
        usart1_sendbyte('0');
        return;
    }
    while(num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num = num / 10;
    }
    while(i > 0)
    {
        usart1_sendbyte(buffer[--i]);
    }
}

int main(void)
{
    // Llamamos a las funciones de tus librerías en lugar de configurarlo todo aquí
    GPIO_PC13_Init();   // Prepara el pin del LED[cite: 11]
    init_exti_pin();    // Prepara el pin de la interrupción PA0[cite: 10]
    init_exti();        // Configura la interrupción[cite: 10]
    
    // Asumiendo que combinaste la configuración de pines dentro de init_usart1() como vimos antes
    init_usart1();      

   while(1)
{
    usart1_sendbyte('\r');          // Volver al principio de la línea
    usart1_sendstring("Pulsos: ");
    usart1_enviar_numero(contador_pulsos);

    // Retardo aproximado 1 s
    for(uint32_t t=0; t<7200000; t++);
}
}