#include <stdint.h>
#include "stm32f411xe.h"
#include "tim.h"

void tim2_init(void) {
//enable TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//	TIMx_CR1, TIMx_CR2 (Control registers) → configuring update events (UEVs, when the timeout/auto-reload occurs)
	// TIM2->CR1 |= TIM_CR1_CEN_Msk;
	TIM2->CR1 |= TIM_CR1_DIR; // down counting mode
	TIM2->CR1 &= ~TIM_CR1_CMS;

	//	TIMx_SR (Status register) → a UEV has occurred, and other flags

	//	TIMx_CNT (Counter register)
	TIM2->CNT = 3000 - 1;	// automatically set to 3000 to start count down

	//	TIMx_PSC (Prescaler register)
	TIM2->PSC = 16000 - 1; // 16,000,000 / 16,000 = 1000

	//	TIMx_ARR (Auto-reload register)
	TIM2->ARR = 3000 - 1; // 1000 ticks per second, 3 seconds count down

	TIM2->EGR |= TIM_EGR_UG; // force PSC and ARR values to be written

}

void tim5_init(void) {
//enable TIM5
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

	//	TIMx_CR1, TIMx_CR2 (Control registers) → configuring update events (UEVs, when the timeout/auto-reload occurs)
	// TIM5->CR1 |= TIM_CR1_CEN_Msk;
	TIM5->CR1 &= ~TIM_CR1_DIR; // up counting mode
	TIM5->CR1 &= ~TIM_CR1_CMS;

	//	TIMx_SR (Status register) → a UEV has occurred, and other flags

	//	TIMx_CNT (Counter register)

	//	TIMx_PSC (Prescaler register)
	TIM5->PSC = 16000 - 1;

	//	TIMx_ARR (Auto-reload register)
	TIM5->ARR = 10000 - 1; // max of 10 seconds given for reaction time

	TIM5->EGR |= TIM_EGR_UG; // force PSC and ARR values to be written

}

void tim2_start(void) {
	TIM2->CR1 |= TIM_CR1_CEN;
}

void tim5_start(void) {
	TIM5->CR1 |= TIM_CR1_CEN;
}

void tim2_stop(void) {
	TIM2->CR1 &= ~TIM_CR1_CEN;
}

void tim5_stop(void) {
	TIM5->CR1 &= ~TIM_CR1_CEN;
}

void tim2_reset(void) {
	TIM2->CNT = 3000 - 1;
}

void tim5_reset(void) {
	TIM5->CNT = 0;
}

uint32_t get_tim2_ms(void) {
	return TIM2->CNT;
}

uint32_t get_tim5_ms(void) {
	return TIM5->CNT;
}

//uint32_t tim2_zero(void) {
//	return (TIM2->SR & TIM_SR_UIF);
//}



