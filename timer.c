#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "buttons.h"
#include "leds.h"


/*I need a clock frequency of 400 kHz to achieve timing over a maximum value of 10800. Internal clock is 3 MHz default*/
void reset(void);
void changeTime(void);
void setup_timer(void){

    uint32_t count = 1*187.5E3;

    /*Initializes the Timer32 Module. Divided clock signal by 16
     * and set the timer to 32 bit mode. We need to be able to count down from 10800
     * seconds which is 3 hours. This is the maximum time we can run the sign at.
     * Sets the clock signal for the timer32 at 187.5 kHz
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
 * trigger the decrement of the counter
 */
    MAP_Timer32_registerInterrupt(TIMER32_0_INTERRUPT,&changeTime);

    /*
     * Sets the count the timer will count down from.
     */
    MAP_Timer32_setCount(TIMER32_0_BASE,count);

    changetime = 0;

    COUNTDOWN = true;

}
void reset(void){
    Timer32_haltTimer(TIMER32_0_BASE); //stops the timer
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE);
    LEDOFF();
    time = 0;
    RESET = true;
    COUNTDOWN = false;
    SETTIME = false;

}
void changeTime(void){
    /* Everytime the interrupt is registered, the interrupt flag must be cleared */
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE);
    timeseconds--; //subtracts 1
    changetime++; //variable which keeps track of how many seconds have been counted
    if(changetime == 60){ //at 60 seconds counted, the time (minutes) variable is decremented
        time--;
        changetime = 0;
    if(time == 0){ //puts the device back into the reset state
        reset();
    }
}

}
