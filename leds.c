#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "buttons.h"
#include "timer.h"

void LEDOFF(void){
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN6);
    LED_ON = false;
}
void LEDON(void){
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN6);
    Timer32_startTimer(TIMER32_0_BASE,true);
    LED_ON = true;
}
