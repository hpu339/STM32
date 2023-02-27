#ifndef _PWM_H
#define _PWM_H


void PWM_TIM2Init();
void PWM_Set(uint16_t ccr);
void PWM_FreqSet(uint16_t prescaler);

#endif // !_PWM_H
