/*
 * buzzer.h
 *
 *  Buzzer Driver .h file (Header file)
 *      Author: hnelamir
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*                    Definitions                     */
#define BUZZER_PORT_ID			PORTB_ID
#define BUZZER_PIN_ID			PIN4_ID

/*                    Prototypes                     */


void Buzzer_init();

/*Function to enable the Buzzer */
void Buzzer_on(void);
/*Function to disable the Buzzer*/
void Buzzer_off(void);
#endif /* BUZZER_H_ */
