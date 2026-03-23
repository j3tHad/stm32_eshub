#include <stdint.h>
#include "stm32f411xe.h"
#include "gpio.h"

void led_init(void)
{
// enable PA5
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

}

void button_init(void)
{
// enable PC13
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// input mode
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

}

int button_pressed() {

	static int prev_state = 0; // button is active low
	int curr_state = button_state(); // Returns 1 for released, 0 for pressed
	int pressed = 0;

	if (prev_state == 1 && curr_state == 0)
	{
		for(volatile int i = 0; i < 64000; i++);

		if (button_state() == 0)
			pressed = 1;
	}
	prev_state = curr_state;
	return pressed;

}

uint32_t button_state(void)
{
	return !(GPIOC->IDR & (1U << 13));
}

void led_on(void)
{
	GPIOA->ODR |= (1U << 5);
}

void led_off(void)
{
	GPIOA->ODR &= ~(1U << 5);
}
