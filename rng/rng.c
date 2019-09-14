// CAUTION: THIS LIBRARAY IS NOT WORKING YET

void initRng(void) {

    RCC->CR |= RCC_CR_MSION;
    RCC->CR &= ~(0b1111 << RCC_CR_MSIRANGE_Pos);
    RCC->CR |= (0b0110 << RCC_CR_MSIRANGE_Pos);
    RCC->CR |= RCC_CR_PLLON;
    RCC->PLLCFGR &= ~(0b11 << RCC_PLLCFGR_PLLSRC_Pos);
    RCC->PLLCFGR |= 0b01 << RCC_PLLCFGR_PLLSRC_Pos;
    RCC->PLLCFGR &= ~(0b111 << RCC_PLLCFGR_PLLM_Pos);
    RCC->PLLCFGR &= ~(0b1111111 << RCC_PLLCFGR_PLLN_Pos);
    RCC->PLLCFGR |= 40 << RCC_PLLCFGR_PLLN_Pos;
    RCC->PLLCFGR &= ~(1 << RCC_PLLCFGR_PLLP_Pos);
    RCC->PLLCFGR &= ~(0b11 << RCC_PLLCFGR_PLLQ_Pos);
    RCC->PLLCFGR &= ~(0b11 << RCC_PLLCFGR_PLLR_Pos);
    RCC->CCIPR &= ~(0b11 << RCC_CCIPR_CLK48SEL_Pos);
    RCC->CCIPR |= 0b10 << RCC_CCIPR_CLK48SEL_Pos;


    RCC->PLLCFGR |= RCC_PLLCFGR_PLLQEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
    RNG->CR |= RNG_CR_RNGEN;

    // maybe hsi48on?
}

uint8_t areClocksSuccessfullyConfigured(void){
    // while (!(RNG->SR & (RNG_SR_DRDY)));
    // while (!(RNG->SR & RNG_SR_DRDY) || (RNG->SR & (RNG_SR_SEIS) || (RNG->SR & (RNG_SR_CEIS) )));
    return (RNG->SR & RNG_SR_CECS) >> 1;
}

uint32_t getRandomNumber(void){
    // while (!(RNG->SR & (RNG_SR_DRDY)));
    while (!(RNG->SR & RNG_SR_DRDY) || (RNG->SR & (RNG_SR_SEIS) || (RNG->SR & (RNG_SR_CEIS) )));
    return RNG->DR;
}