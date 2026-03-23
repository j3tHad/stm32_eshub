#include <stdint.h>
#include "stm32f411xe.h"
#include "gpio.h"

void gpio_en(void)
{
// enable PA5
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

	// output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

// enable PC13
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;

	// input mode
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

}

uint32_t button_state(void)
{
	return !(GPIOC->IDR & (1U << 13));
}

void toggle_led(void)
{
	GPIOA->ODR ^= (1U << 5);
}
