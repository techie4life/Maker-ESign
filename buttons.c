

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "buttons.h"
#include "timer.h"

static ButtonPin b1 = {.port = GPIO_PORT_P2 , .pin= GPIO_PIN4};
static ButtonPin b2 = {.port = GPIO_PORT_P2 , .pin= GPIO_PIN5};
static ButtonPin b3 = {.port = GPIO_PORT_P3 , .pin= GPIO_PIN2};


void button_setup(void){

    /* setup physical configuration */
        MAP_GPIO_setAsInputPinWithPullDownResistor(b1.port, b1.pin);
        MAP_GPIO_setAsInputPinWithPullDownResistor(b2.port, b2.pin);
        MAP_GPIO_setAsInputPinWithPullDownResistor(b3.port, b3.pin);

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
        MAP_GPIO_registerInterrupt(b3.port, &Reset);

        /* enable interrupts for specific pins */
        MAP_GPIO_enableInterrupt(b1.port, b1.pin);
        MAP_GPIO_enableInterrupt(b2.port, b2.pin);
        MAP_GPIO_enableInterrupt(b3.port, b3.pin);


        /* enable interrupt in interrupt controller */
        MAP_Interrupt_enableInterrupt(INT_PORT2);
        MAP_Interrupt_enableInterrupt(INT_PORT3);

}

void handleButtonPress(void){
    uint32_t status;
    status = MAP_GPIO_getEnabledInterruptStatus(b1.port);

    if((status & b1.pin) && (status & b2.pin))
        return;
    else if(status & b1.pin)
        handleStart();

    else if(status & b2.pin)
        handleUp();

}
void handleStart(void){
if(time = 0)
    return;
else if(time>0)
    setup_timer();

}
