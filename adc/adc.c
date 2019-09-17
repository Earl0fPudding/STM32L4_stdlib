void initAdc1(void){
    RCC->AHB2ENR|=RCC_AHB2ENR_ADCEN; // enable adc for the bus
    RCC->CCIPR|= 0b11 << RCC_CCIPR_ADCSEL_Pos; // system clock as adc clock
    ADC1_COMMON->CCR|= ADC_CCR_VREFEN; // enable reference voltage

    ADC1->CFGR &= ~ADC_CFGR_RES_Pos; // 12 bit resolution

    // calibrate the adc
    ADC1->CR &= ~ADC_CR_DEEPPWD; // adc not in low power mode
    ADC1->CR |= ADC_CR_ADVREGEN;
    for (uint16_t i = 0; i < 10000; ++i) {
        __NOP();
    }
    ADC1->CR &= ~ADC_CR_ADEN;
    ADC1->CR &= ~ADC_CR_ADCALDIF; // single ended input
    ADC1->CR |=ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);

    ADC1_COMMON->CCR |= ADC_CCR_TSEN; // enable temperature sensor

    //set input
    ADC1->SQR1 &= ~ADC_SQR1_L; // 1 conversion
    ADC1->SQR1 |= 17 << ADC_SQR1_SQ1; // temp sensor on sequence 1

    // enable the adc
    ADC1->ISR |=ADC_ISR_ADRDY;
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));
    ADC1->ISR |=ADC_ISR_ADRDY;
}

uint16_t getAdc1Conversion(void){
    ADC1->CR |=ADC_CR_ADSTART;
    while (!(ADC1->ISR & ADC_ISR_EOC));
    return ADC1->DR;
}