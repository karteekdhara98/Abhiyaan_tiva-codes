#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/qei.h"

volatile int qeiPosition;


void setup() {

  // Set the clocking to run directly from the crystal.
  SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

  // Enable QEI Peripherals
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);

  //Unlock GPIOD7 - Like PF0 its used for NMI - Without this step it doesn't work
  HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //In Tiva include this is the same as "_DD" in older versions (0x4C4F434B)
  HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
  HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;

  //Set Pins to be PHA0 and PHB0
GPIOPinConfigure(0x00031806);  // 0x00031806 =>GPIO_PD6_PHA0
GPIOPinConfigure(0x00031C06);  // 0x00031C06 => GPIO_PD7_PHB0
  //Set GPIO pins for QEI. PhA0 -> PD6, PhB0 ->PD7. I believe this sets the pull up and makes them inputs
  GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_6 |  GPIO_PIN_7);

  //DISable peripheral and int before configuration
  QEIDisable(QEI0_BASE);
  QEIIntDisable(QEI0_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);

  // Configure quadrature encoder, use an arbitrary top limit of 1000
  QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET  | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 1000);

  // Enable the quadrature encoder.
  QEIEnable(QEI0_BASE);

  //Set position to a middle value so we can see if things are working
  QEIPositionSet(QEI0_BASE, 500);
  
  //Add qeiPosition as a watch expression to see the value inc/dec
}
void loop() //This is the main loop of the program
  {
    qeiPosition = QEIPositionGet(QEI0_BASE);
    SysCtlDelay (1000);
  }

