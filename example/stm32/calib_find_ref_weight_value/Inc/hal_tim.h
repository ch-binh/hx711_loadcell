
#ifndef __TIM_H__
#define __TIM_H__

#include "main.h"

extern TIM_HandleTypeDef htim2;

void MX_TIM2_Init(void);
void hal_tim_busy_wait_us(uint16_t us);

#endif /* __TIM_H__ */
