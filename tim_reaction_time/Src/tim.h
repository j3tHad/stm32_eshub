#ifndef TIM_H_
#define TIM_H_

void tim2_init(void);
void tim5_init(void);
void tim2_start(void);
void tim5_start(void);
void tim2_stop(void);
void tim5_stop(void);
void tim2_reset(void);
void tim5_reset(void);
uint32_t get_tim2_ms(void);
uint32_t get_tim5_ms(void);
//uint32_t tim2_zero(void);

#endif
