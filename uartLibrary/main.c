#include <msp430g2553.h>
#include <UART.h>


int main(void)
{
    char vel [] = "Hello";
    char data ;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    setupClock();               //setup smclk
    uartInit();                 //setup the uart registers
    //uartSend("sakib");        // send whatever string you wanna send
    //uartSend(vel);            //send whatever string you wanna send


    while (1)
    {
        if (uartAvailable())        // check Byte availability
        {
            if (uartReceive() == 's')
            {
                P1OUT ^= BIT0;
            }
        }
    }

}
