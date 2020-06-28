#include "msp430x22x4.h"


/**
 * main.c
 */

volatile unsigned int i,timcnt;
void configureclocks1()
{
    //set system DCO to 8MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    // Set LFXT1 to the VLO @ 12kHz
    BCSCTL3 |= LFXT1S_2;
}

void configureclocks2()
{
    //set system DCO to 8MHz
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;

    // Set LFXT1 to the VLO @ 12kHz
    BCSCTL3 |= LFXT1S_2;
}
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    timcnt = 0;


    P1DIR = BIT0;
    for (;;)
    {

        P1OUT ^= BIT0;
        timcnt++;


        if (timcnt <= 5)
        {
            configureclocks1();
        }
        else
        {
            configureclocks2();
            if (timcnt == 10)
            {
                timcnt = 0;
            }
        }
        i = 10000;
        do(i--);
        while (i!=0);
    }
}
