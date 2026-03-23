#ifndef GPIO_H_
#define GPIO_H_

void led_init(void);
void button_init(void);
uint32_t button_state(void);
int button_pressed(void);
void led_on(void);
void led_off(void);

#endif
