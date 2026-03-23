#include <stdint.h>
#include "stm32f411xe.h"
#include "systick.h"

void systick_en(void)
{
// SYST->CSR
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
	// SYST->CSR

// SYST->RVR
	SysTick->LOAD = 1000000 - 1;	// 1Hz, 0.5s, 1000000 ticks
	// when count reaches 0, switch light to on/off

// SYST->CVR

// SYST->CALIB

}

void delay_ms(uint32_t ms)
{
	int ticks = (ms * 2000) - 1;
	SysTick->LOAD = ticks;
	SysTick->VAL = 0;	// clear current value in counter
}

uint32_t count_zero(void)
{
	// check if counter reached 0
	return (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk);
}
