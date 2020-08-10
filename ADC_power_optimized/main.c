#include "msp430g2553.h"

void configureClockForADC(void);
void configureADC10(int BIT_NO);
void shutDownADC(void);
volatile int ADC_result = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                           // Stop WDT
    configureClockForADC();                             // clocks set to SMCLK
    configureADC10(BIT0);                               // configuring ADC. Also change the INCH_x bit in ADC10CTL1 register
    __enable_interrupt();                               // Enable interrupts
    ADC10CTL0 |= ENC + ADC10SC;                         // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);                    // Low Power Mode 0 with interrupts enabled
    shutDownADC();                                      // stop ADC operation

}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    ADC_result = ADC10MEM;                              // Assigns the value held in ADC10MEM to the integer called ADC_value
    __bic_SR_register_on_exit(CPUOFF);                  // Return to active mode
}

void configureClockForADC(void)
{
    DCOCTL = CALDCO_1MHZ;                               // Set range   DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 &= ~(DIVS_3);                               // SMCLK = DCO = 1MHz


}
void configureADC10(int BIT_NO)
{
    P1SEL |= BIT_NO;                                                                                    // ADC input pin P1.0
    ADC10CTL0 &= ENC;                                                                                   // ADC10CTL0 can be modified only when ENC = 0
    ADC10CTL0 |= SREF_0 + ADC10SHT_2 + ADC10SR + REFBURST + REF2_5V + REFON + ADC10ON + ADC10IE;        // select reference as VCC and VSS,
                                                                                                        // Sample and hold time = 16*ADC10Clocks--> minimum 13*ADC10clocks are required
                                                                                                        // ADC10SR --> sampling rate set to 50ksps
                                                                                                        // setting REFBURST will turn on the reference buffer only during conversion. saves power.
                                                                                                        // setting REF2_5V reference generator at 2.5V
                                                                                                        // REFON turns on reference generator
                                                                                                        // ADC10ON turns ADC10 on
                                                                                                        // ADC10IE --> Interrupt enable
    // ADC10CTL0 |= ENC;                                                                                // Enable conversion
    ADC10CTL1 |= INCH_0 + SHS_0 + ADC10DIV_7 + ADC10SSEL_3 + CONSEQ_0;                                  // Input channel selected --> A0,
                                                                                                        // SHS_0 --> ADC10OSC as sample and hold source. saves power as it turns of while no conversion is active
                                                                                                        // ADC10DIV_7--> ADC10CLock/8
                                                                                                        // ADC10SSEL_3 --> clock source = SMCLK
                                                                                                        // CONSEQ_0 --> Single-channel-single-conversion
    ADC10AE0 = BIT_NO;                                                                                  // select pin1.0 as ADC input
}

void shutDownADC(void)
{
    while (ADC10CTL1 & ADC10BUSY);                      // check ongoing conversion
    ADC10CTL0 &= ~(ENC + ADC10SC);                      // Stop conversion
    ADC10CTL0 &= ~ADC10ON;                              // shut down ADC
}
