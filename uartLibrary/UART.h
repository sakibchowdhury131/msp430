
#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#include <msp430g2553.h>


void setupClock(void);
void uartInit(void);
void uartSend(char vel[]);
int uartAvailable(void);
char uartReceive();


#endif
