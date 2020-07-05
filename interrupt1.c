#include "msp430g2553.h"

#define LED BIT0                                //p1.0 for led

void main ()
{
    WDTCTL = WDTPW + WDTHOLD;                    // stop the watchdog timer
    BCSCTL1 = CALBC1_8MHZ;
    BCSCTL2 |=  DIVS_2 ;
    BCSCTL3 |= LFXT1S_2;

    P1DIR = LED;
    TA0CCR0 = 0xFF00;
    TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;            // select source: SMCLK, Divider = 4, Mode = up mode

    while (1)
    {
        while ((TA0CTL & TAIFG) == 0)           // check interrupt flag of timerA
        {
            //TA0CTL |= TACLR;
        }

        TA0CTL &= ~TAIFG;
        P1OUT ^= LED;
    }
}
