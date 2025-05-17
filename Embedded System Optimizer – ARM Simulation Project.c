#include "stm32f4xx.h"

// Global variables
volatile uint32_t cycles_taken = 0;

void init_GPIO(void);
void init_EXTI(void);
void init_DWT_CycleCounter(void);

int main(void) {
    SystemInit(); // Initialize system clock
    init_GPIO();
    init_EXTI();
    init_DWT_CycleCounter();

    while (1) {
        __WFI(); // Wait for interrupt - low power
    }
}

// Configure GPIO for LED (PD12) and Button (PA0)
void init_GPIO(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN;

    // PD12 output (LED)
    GPIOD->MODER |= (1 << (2 * 12)); // Output mode

    // PA0 input (Button)
    GPIOA->MODER &= ~(3 << (2 * 0)); // Input mode
}

// Configure EXTI0 interrupt for PA0
void init_EXTI(void) {
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;

    EXTI->IMR  |= EXTI_IMR_MR0;
    EXTI->FTSR |= EXTI_FTSR_TR0;

    NVIC_SetPriority(EXTI0_IRQn, 0); // High priority
    NVIC_EnableIRQ(EXTI0_IRQn);
}

// Initialize DWT Cycle Counter
void init_DWT_CycleCounter(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

// EXTI0 ISR (PA0)
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {
        EXTI->PR |= EXTI_PR_PR0; // Clear interrupt

        uint32_t start = DWT->CYCCNT;

        // Minimal ISR logic
        GPIOD->ODR ^= (1 << 12); // Toggle LED

        uint32_t end = DWT->CYCCNT;
        cycles_taken = end - start; // Cycle count difference
    }
}
