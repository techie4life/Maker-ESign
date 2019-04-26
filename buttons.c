
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "buttons.h"
#include "timer.h"
#include "leds.h"

/*
 * Start = P2.4
 * Time-Up = P2.5
 * Reset = P3.2
 */

static ButtonPin b1 = {.port = GPIO_PORT_P2 , .pin= GPIO_PIN4}; //start
static ButtonPin b2 = {.port = GPIO_PORT_P2 , .pin= GPIO_PIN5}; //time up
static ButtonPin b3 = {.port = GPIO_PORT_P3 , .pin= GPIO_PIN2}; //reset


void button_setup(void){

    /* setup physical configuration */
        MAP_GPIO_setAsInputPinWithPullDownResistor(b1.port, b1.pin);
        MAP_GPIO_setAsInputPinWithPullDownResistor(b2.port, b2.pin);
        MAP_GPIO_setAsInputPinWithPullDownResistor(b3.port, b3.pin);
        MAP_GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN6);

        /* setup interrupts */
        MAP_GPIO_clearInterruptFlag(b1.port, b1.pin);
        MAP_GPIO_clearInterruptFlag(b2.port, b2.pin);
        MAP_GPIO_clearInterruptFlag(b3.port, b3.pin);

        /* assume an active high transition with button press defined as
         * the moment the button is pushed down
         */
        MAP_GPIO_interruptEdgeSelect(b1.port, b1.pin, GPIO_LOW_TO_HIGH_TRANSITION);
        MAP_GPIO_interruptEdgeSelect(b2.port, b2.pin, GPIO_LOW_TO_HIGH_TRANSITION);
        MAP_GPIO_interruptEdgeSelect(b3.port, b3.pin, GPIO_LOW_TO_HIGH_TRANSITION);

        /* register interrupt handler */
        MAP_GPIO_registerInterrupt(b1.port, &handleButtonPress);
        MAP_GPIO_registerInterrupt(b3.port, &reset);

        /* enable interrupts for specific pins */
        MAP_GPIO_enableInterrupt(b1.port, b1.pin);
        MAP_GPIO_enableInterrupt(b2.port, b2.pin);
        MAP_GPIO_enableInterrupt(b3.port, b3.pin);


        /* enable interrupt in interrupt controller */
        MAP_Interrupt_enableInterrupt(INT_PORT2);
        MAP_Interrupt_enableInterrupt(INT_PORT3);

        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN6);
        /*
         * Sets the time value to zero initially
         */
        time = 0; //initial time
        RESET = true; //reset state
        COUNTDOWN = false; //countdown state, when the timer is running
        SETTIME = false; //state where a time != 0

}

void handleButtonPress(void){
    uint32_t status;
//stores the value of the button which generated the interrupt
    status = MAP_GPIO_getEnabledInterruptStatus(b1.port);

    /* clear the interrupt flag to indicate we have handled interrupt */
    MAP_GPIO_clearInterruptFlag(b1.port, status);

//Checks if both buttons are pressed simultaneously
    if((status & b1.pin) && (status & b2.pin));


//checks if button 1 was pressed
    else if(status & b1.pin){
        handleStart();
    }
//checks if button 2 was pressed
    else if(status & b2.pin){
        handleUp();
        SETTIME = true;
        RESET = false;
    }
}
//Deals with the 'start' button press
void handleStart(void){

if(time>0 && (SETTIME == true) && (RESET == false)){
    setup_timer();
    LEDON();
}
}
void handleUp(void){
    time = time + 15; //minutes
    timeseconds = time * 60; //seconds
}
