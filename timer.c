#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "buttons.h"
#include "leds.h"
#define     TIMER32_0_INTERRUPT   INT_T32_INT1
#define     TIMER32_1_INTERRUPT   INT_T32_INT2

/*I need a clock frequency of 400 kHz to achieve timing over a maximum value of 10800. Internal clock is 3 MHz default*/
void reset(void);
void setup_timer(void){

    long count = time*3E6;

    /*Initializes the Timer32 Module. Divided clock signal by 16
     * and set the timer to 32 bit mode. We need to be able to count down from 10800
     * seconds which is 3 hours. This is the maximum time we can run the sign at.
     */
    MAP_Timer32_initModule(TIMER32_0_BASE,TIMER32_PRESCALER_16,TIMER32_32BIT,TIMER32_PERIODIC_MODE);

    /*Clears the interrupt flag for the timer
     */
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE);

    /*
     * Enables interrupt for the the timer32 module
     */
    MAP_Timer32_enableInterrupt(TIMER32_0_BASE);

    MAP_Interrupt_enableInterrupt(INT_T32_INT1);
/*
 * Once the timer finishes its counting, an interrupt will be generated and will
 * trigger the shut off of the LEDs
 */
    MAP_Timer32_registerInterrupt(TIMER32_0_INTERRUPT,&LEDOFF);

    /*
     * Sets the count the timer will count down from.
     */
    MAP_Timer32_setCount(TIMER32_0_BASE,count);

}
void reset(void){
    Timer32_haltTimer(TIMER32_0_BASE); //stops the timer
    time = 0;//sets the time variable to 0.
}

