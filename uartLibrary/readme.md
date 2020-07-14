This library contains 5 functions

1. setupClock()
      this functions sets up SMCLK at 1MHz 
      
2. uartInit()
      this function configures all the required registers
      
3. uartSend(char array)
      this function send a character array 
      
4. uartAvailable()
      returns true if UCA0RXBUF register holds new byte
      
5. uartReceive()
      returns a character byte received. 
      
      
for usage example, see the "main.c" file
