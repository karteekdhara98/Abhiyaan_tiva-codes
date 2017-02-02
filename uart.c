#include "tm4c123gh6pm.h"

char readChar(void);
void printString(char *c);
void printChar(char c);

int main()
{
 SYSCTL_RCGCUART_R = 0x01;
 SYSCTL_RCGCGPIO_R = 0x01;
 GPIO_PORTA_AFSEL_R = 0x03;
 GPIO_PORTA_AFSEL_R = 0x11;
 GPIO_PORTA_DEN_R = 0x03;
 UART0_CTL_R = 0x00;
 UART0_IBRD_R = 104;
 UART0_FBRD_R = 11;
 UART0_LCRH_R = 0x60;
 UART0_CC_R = 0x00;
 UART0_CTL_R = 0x0301;
 
 
 SYSCTL_RCGCGPIO_R |= 0x20;
 GPIO_PORTF_DIR_R = 0x07; 
 GPIO_PORTF_DEN_R = 0x07;
 GPIO_PORTF_DATA_R = 0x00;
 
 while(1)
 {
   printString("Enter r or g or b");
   printString("\n");
   char c = readChar();
   printChar(c);
   printString("\n");
   switch(c)
   {
     case 'r': GPIO_PORTF_DATA_R = 0x02;
     break;
     case 'b': GPIO_PORTF_DATA_R = 0x04;
     break;
     case 'g': GPIO_PORTF_DATA_R = 0x08;
     break;
   default: GPIO_PORTF_DATA_R = 0x00;
   break;
   }
 }
     
 
 
 
 
  
  
  return 0;
}

char readChar(void)
{
  char c;
  while(( UART0_FR_R & 0x10) !=0);
  c= UART0_DR_R;
  return c;
}

void printString(char *string)
{
  while(*string)
  {
    printChar(*(string++));
  }
}

void printChar(char c)
{
    while(( UART0_FR_R & 0x20) !=0);
    UART0_DR_R = c;
}