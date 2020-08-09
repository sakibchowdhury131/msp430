#include "msp430g2553.h"


void configureADC10(void);
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;       // Stop WDT
    BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
    BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
    P1SEL |= BIT0;                  // ADC input pin P1.0
    configureADC10();
    __enable_interrupt();           // Enable interrupts

    while (1)
    {
        ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
        __bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
    }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    volatile int ADC_result = 0;
    ADC_result = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value
    __bic_SR_register_on_exit(CPUOFF);        // Return to active mode }
}

void configureADC10()
{
    ADC10CTL0 &= ENC;
    ADC10CTL0 |= SREF_0 + ADC10SHT_2 + ADC10SR + REFBURST + REF2_5V + REFON + ADC10ON + ADC10IE;
    ADC10CTL0 |= ENC;
    ADC10CTL1 |= INCH_0 + SHS_0 + ADC10DIV_7 + ADC10SSEL_3 + CONSEQ_0;
    ADC10AE0 = BIT0;
}
