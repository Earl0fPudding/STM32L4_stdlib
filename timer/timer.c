#include "timer.h"

void initTimer6(void){
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
    TIM6->CR1 |= TIM_CR1_CEN;
    TIM6->PSC=100;
}

void initTimer1(void){
     RCC->APB2ENR|= RCC_APB2ENR_TIM1EN;
     TIM1->CR1 |= TIM_CR1_CEN;
     TIM1->DIER|=TIM_DIER_CC1IE;
     TIM1->PSC=100;
     TIM1->CCR1=40000;
     NVIC_EnableIRQ(TIM1_CC_IRQn);
}

void disableTimer1(void){
    TIM1->CR1 &= ~TIM_CR1_CEN;
    TIM1->CNT=0;
}

void wait_us(uint16_t us){
    __disable_irq();
    for (uint16_t i = 0; i < us; ++i) {
        TIM6->CNT=0;
        while (TIM6->CNT < 1) { }
    }
    __enable_irq();
}

void wait_seconds(uint8_t secs){
    for (uint8_t i = 0; i < secs; ++i) {
        __disable_irq();
        TIM6->CNT=0;
        while (TIM6->CNT < 40000) { }
        __enable_irq();
    }
    //wait_ms(secs*1000);
}

void wait_ms(uint16_t ms){
    for (uint16_t i = 0; i < ms; ++i) {
        __disable_irq();
        TIM6->CNT=0;
        while (TIM6->CNT < 40) { }
        __enable_irq();
        //__NOP();
    }
}