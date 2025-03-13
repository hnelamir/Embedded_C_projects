/*
 * dc_motor.h
 *
 *	DC motor Driver .h file (Header file)
 *      Author: hnelamir
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include "gpio.h"
/* types  */
typedef enum {
	STOP,CLOCKWISE,ANTI_CLOCKWISE
}DCMotor_State;

/* Definitions for motor pins */

#define DCMotor_P0_PORT_ID    PORTA_ID
#define	DCMotor_P0_PIN_ID	  PIN3_ID

#define DCMotor_P1_PORT_ID    PORTA_ID
#define	DCMotor_P1_PIN_ID     PIN4_ID
/* Function prototype  */


/* The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
*/
void DCMotor_init(void);

/* The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
 *    required speed value.
 */
void DCMotor_Rotate(DCMotor_State state, uint8 speed);
#endif /* DC_MOTOR_H_ */
