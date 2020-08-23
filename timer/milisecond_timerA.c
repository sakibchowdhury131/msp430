#include <msp430.h>
#define BLINKY_DELAY_MS 500 //Change this as per your needs

void initTimer_A(void);
void delayMS(int msecs);

unsigned int OFCount;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
    P1DIR |= BIT0; //Configure P1.0 as Output

    //Set MCLK = SMCLK = 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    initTimer_A();
    _enable_interrupt();

    OFCount  = 0;
    TACCR0 = 1000-1; //Start Timer, Compare value for Up Mode to get 1ms delay per loop
    /*Total count = TACCR0 + 1. Hence we need to subtract 1.
    1000 ticks @ 1MHz will yield a delay of 1ms.*/

    while(1);
}

void initTimer_A(void)
{
    //Timer Configuration
    TACCR0 = 0; //Initially, Stop the Timer
    TACCTL0 |= CCIE; //Enable interrupt for CCR0.
    TACTL = TASSEL_2 + ID_0 + MC_1; //Select SMCLK, SMCLK/1 , Up Mode
}

//Timer ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0_ISR(void)
{
    OFCount++;
    if(OFCount >= BLINKY_DELAY_MS)
    {
        P1OUT ^= BIT0;
        OFCount = 0;
    }
}
