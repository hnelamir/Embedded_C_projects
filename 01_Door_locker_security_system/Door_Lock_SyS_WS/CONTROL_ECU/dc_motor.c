/*
 * dc_motor.c
 *
 *  DC motor Driver .c file (Source File)
 *      Author: hnelamir
 */

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/* Function Definitions */


void DCMotor_init(void){

/* Initializing the motor pins as output pin */
	GPIO_setupPinDirection(PORTA_ID,DCMotor_P0_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,DCMotor_P1_PIN_ID,PIN_OUTPUT);

/* Stop Dc motor at the start*/
	GPIO_writePin(PORTA_ID,DCMotor_P0_PIN_ID,LOGIC_LOW);
	GPIO_writePin(PORTA_ID,DCMotor_P1_PIN_ID,LOGIC_LOW);

}

void DCMotor_Rotate(DCMotor_State state, uint8 speed){
	uint8 duty_cycle;

	switch(state){
		case CLOCKWISE:
			GPIO_writePin(PORTA_ID,DCMotor_P0_PIN_ID,LOGIC_HIGH);
			GPIO_writePin(PORTA_ID,DCMotor_P1_PIN_ID,LOGIC_LOW);
			break;
		case ANTI_CLOCKWISE:
			GPIO_writePin(PORTA_ID,DCMotor_P0_PIN_ID,LOGIC_LOW);
			GPIO_writePin(PORTA_ID,DCMotor_P1_PIN_ID,LOGIC_HIGH);
			break;
		case STOP:
			GPIO_writePin(PORTA_ID,DCMotor_P0_PIN_ID,LOGIC_LOW);
			GPIO_writePin(PORTA_ID,DCMotor_P1_PIN_ID,LOGIC_LOW);
			break;
		default:
			return;
	}
	duty_cycle=((uint8)(((uint16)(speed * TOP))/100));
	PWM_Timer0_Start(duty_cycle);
}
