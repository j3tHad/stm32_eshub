#include <stdint.h>
#include "stm32f411xe.h"
#include "adc.h"

void adc_en(void) {

	/****** enable GPIO pin PA0 ******/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

	// set to ANALOG mode
	GPIOA->MODER |= (1U << 0);
	GPIOA->MODER |= (1U << 1);


	/******** enable ADC registers ********/
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN_Msk;

//	ADC_SQRx (Regular Sequence Register)
	ADC1->SQR1 = 0x0; // one conversion only (channel)
	ADC1->SQR3 = ~ADC_SQR3_SQ1_Msk;

//	ADC_CR1 (Control Register 1)
	// set resolution to 12-bit, (15 ADC_clk cycles)
	ADC1->CR1 &= ~ADC_CR1_RES_Msk;

//	ADC_CR2 (Control Register 2)
	ADC1->CR2 |= ADC_CR2_ADON_Msk;
	ADC1->CR2 &= ~ADC_CR2_ALIGN_Msk; // right align

}


uint32_t adc_get(void) {

	// start conversion
	ADC1->CR2 |= ADC_CR2_SWSTART_Msk;

	while (!(ADC1->SR & ADC_SR_EOC_Msk));

	return ADC1->DR;
}

