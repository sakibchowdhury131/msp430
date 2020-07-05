#include "msp430g2553.h"

#define LED0 BIT0;
#define LED1 BIT1;

void main (void)
{
    WDTCTL = WDTPW + WDTHOLD;                            // watchdog timer turned off
    TA0CCTL0 |= CCIE;                                    //TA0CCTL interrupt enable
    TA1CCTL0 |= CCIE;                                    //TA0CCTL interrupt enable
    TA0CTL = TASSEL_2 + MC_1 + ID_2 + TACLR;             // configuring timerA0
    TA1CTL = TASSEL_2 + MC_1 + ID_2 + TACLR;             // configuring timerA1
    P1DIR = LED0;                                        // setting LED as output
    P1DIR = LED1;                                        // setting LED as output
    P1OUT |= LED0;                                       // turning on LED
    P1OUT &= ~LED1;
    TA0CCR0 = 5000;                                      // setting the limit for the timer
    TA1CCR1 = 5000;
    __bis_SR_register (CPUOFF+GIE);                      //Low power mode and General Interrupt Enable
    while (1)
    {

    }
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= LED0;                                       // toggling LED
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_B(void)
{
    P1OUT ^= LED1;                                       // toggling LED
}
