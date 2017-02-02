#include "tm4c123gh6pm.h"

char readChar(void);
void printString(char *c);
void printChar(char c);
char InputtoQEI0(void);


int main{
SYSCTL_RCGCQEI_R = 0x03;     // Both QEI modules enabled
SYSCTL_RCGCUART_R = 0x01;    // UART Module 0 enabled
SYSCTL_RCGCGPIO_R = 0x0A;    // Activated Port B and D
SYSCTL_RCGCGPIO_R |= 0x01;   // Activated Port A for UART
SYSCTL_RCGCGPIO_R |= 0x04;   // Activated Port C for QEI
SYSCTL_RCGCGPIO_R |= 0x020;   // Activated Port F for QEI
GPIO_PORTB_DIR_R  = 0xFF;    // Declared B as output
GPIO_PORTD_DIR_R  = 0xFF;    // Declared D as output
GPIO_PORTD_DEN_R = 0xFF;     // D's pins are now digital
GPIO_PORTF_LOCK_R = 0x4C4F434B // We need PF0 for PhA0 so unlock
GPIO_PORTF_CR_R = 0x001;      // PF0 can have AFSEL now
GPIO_PORTC_AFSEL_R = 0x70;    // AFSEL for pins 4(IDX1),5(PhA1),6(PhB1)
GPIO_PORTF_AFSEL_R = 0x013;   // AFSEL for pins 0(PhA0),1(PhB0),4(IDX0)
GPIO_PORTC_PCTL_R = 0x6660000; // MUX value 6   
GPIO_PORTF_PCTL_R = 0x60066; // MUX value 6   
SYSCTL_RCGC0_R = 0x00100000;  // PWM clock enabled
SYSCTL_RCGC2_R = 0x00002;     // Port B will be used so clock enable
GPIO_PORTA_AFSEL_R = 0x003;   // Activating Alternate fn in Pins 0,1 of Port A for UART
GPIO_PORTA_PCTL_R = 0x11;     // To assign UART signal to appropriate Pins
GPIO_PORTA_DEN_R = 0x03;      // Pins of A are now digital
UART0_CTL_R = 0x00;           // Disabling UART before operation starts
UART0_IBRD_R = 104;            // Integer portion of Baud Rate 
UART0_FBRD_R = 11;             // Fractional Portion of Baud Rate
UART0_LCRH_R = 0x60;           // SerialParametersthiscase,8 bit,noparity1stopbit 
UART0_CC_R = 0x00;             // Configuring UART clock(this case system clock)
QEI0_CTL_R =  0x00000018;      // Capmode on both PhA and PhB counted, positional resolution double range half and pos. counter reset when index pulse detected 
QEI1_CTL_R =  0x00000018;      // Capmode on both PhA and PhB counted, positional resolution double range half and pos. counter reset when index pulse detected
QEI0_MAXPOS_R =  0x00000F9F;   //  A 1000-line encoder with four edges/line,results in 4000 pulses per revolution; therefore, set the maximum position to 3999 (0xF9F
QEI1_MAXPOS_R =  0x00000F9F;   //  A 1000-line encoder with four edges/line,results in 4000 pulses per revolution; therefore, set the maximum position to 3999 (0xF9F


GPIO_PORTB_AFSEL_R = 0x00C0;    // Port B pins for alt fn
GPIO_PORTB_PCTL_R = 0x44000000; // To assign PWM signals to PB 6 & 7
SYSCTL_RCC_R = 0x0100000;    // 
PWM0_CTL_R = 0x00000000;
PWM0_0_GENA_R =0x0000008C;
PWM0_0_GENB_R = 0x0000080C;
PWM0_0_CMPA_R =  0x0000012B;
PWM0_0_CMPB_R =   0x0000012B;
PWM0_0_LOAD_R = 0x0000012F;  // 320 ticks per minute as apni clock is 16Mhz
PWM0_CTL_R = 0x00000001;
PWM0_ENABLE_R =  0x00000003;   // PWM enabled
UART0_CTL_R = 0x0301;          // UART enabled
QEI0_CTL_R |=  0x00000001;     // Enabling the quadrature Encoder 0 
QEI1_CTL_R |=  0x00000001;     // Enabling the quadrature Encoder 1
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
char InputtoQEI0(void)  // This fn allows you to give 8bits of data to QEI encoder Position Register
{
  char c;
  while(( UART0_FR_R & 0x10) !=0);
  c= UART0_DR_R;
  QEI0_POS_R = UART0_DR_R; 
  return c;
}
void printChar(char c)
{
    while(( UART0_FR_R & 0x20) !=0);
    UART0_DR_R = c;
}