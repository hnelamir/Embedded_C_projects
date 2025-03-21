/*
 * pwm.h
 *
 * PWM Driver .h (header file)
 *      Author: hnelamir
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* PWM HW Ports and Pins Ids */
#define PWM_PORT_ID           PORTB_ID
#define PWM_PIN_ID            PIN3_ID

#define TOP 255

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * The function responsible for trigger the Timer0 with the PWM Mode.
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
