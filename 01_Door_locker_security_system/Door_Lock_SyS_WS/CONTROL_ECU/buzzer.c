/*
 * buzzer.c
 *
 *  Buzzer Driver .c file (Source file)
 *      Author: hnelamir
 */


#include "gpio.h"
#include"buzzer.h"


/*                       Functions                        */
void Buzzer_init()
{


	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

	/* Turn off the buzzer through the GPIO */

	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_LOW);

}

/* Function to enable the Buzzer*/

void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/* Function to disable the Buzzer */

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
