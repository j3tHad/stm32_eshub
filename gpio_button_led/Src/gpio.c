#include <stdint.h>
#include "stm32f411xe.h"
#include "gpio.h"

uint32_t led_en(void) {

	// enable PA5
	RCC->AHB1ENR |= (1U << 0);

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	return (1U << 5);
}

uint32_t button_en(void) {

	// enable PB1
	RCC->AHB1ENR |= (1U << 2);

	GPIOC->MODER &= ~(3U << 26);

	return (1U << 13);
}
