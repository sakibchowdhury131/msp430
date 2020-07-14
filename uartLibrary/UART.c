#include "UART.h"


void setupClock(void)                       // this is for clock setup
{
    if (CALBC1_1MHZ==0xFF)                  // If calibration constant erased
       {
          while(1);                         // do not load, trap CPU!!
       }

     DCOCTL  = 0;                           // Select lowest DCOx and MODx settings
     BCSCTL1 = CALBC1_1MHZ;                 // Set range
     DCOCTL  = CALDCO_1MHZ;                 // Set DCO step + modulation
}



void uartInit(void)                         //this is for register initialization
{
    P1SEL |= BIT1 + BIT2;                   //p1.1 and p1.2 uart pins
    P1SEL2 |= BIT1 + BIT2;                  //P1.1 is UCA0RXD , P1.2 is UCA0TXD


    UCA0CTL1 |= UCSWRST;                    //reset
    UCA0CTL1 |= UCSSEL_2;                   // select SMCLK
    UCA0BR0 = 104;                          // 104 defined in datasheet for 9600 baudrate while SMCLK is selected
    UCA0BR1 = 0x00;                         //ignore
    UCA0MCTL = UCBRS_1;                     //Modulation value 1
    UCA0CTL0 = 0x00;                        //ignore
    UCA0CTL1 &= ~UCSWRST;                   //clear reset
}

void uartSend(char vel[])                   //send function. pass a character array
{
    volatile char i = 0;

    while (vel[i] != '\0')                  //check end of string
    {
        UCA0TXBUF = vel[i];                 //load the buffer
        while (UCA0STAT & UCBUSY);          // check ongoing transmission
        i++;
    }

    UCA0TXBUF = 0x0a;
    while (UCA0STAT & UCBUSY);
    UCA0TXBUF = 0x0d;
    while (UCA0STAT & UCBUSY);

}

int uartAvailable(void)                 //returns true if byte is available
{
    return (UCA0STAT && UCIDLE);
}

char uartReceive(void)
{

    return UCA0RXBUF;                   //return single byte data
                                        // THIS FUNCTION IS ONLY ABLE TO TRANSMIT 1BYTE DATA

}
