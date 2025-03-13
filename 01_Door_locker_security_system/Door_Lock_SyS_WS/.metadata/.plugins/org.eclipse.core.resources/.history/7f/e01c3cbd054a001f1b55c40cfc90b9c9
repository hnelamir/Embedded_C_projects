/*
 * timer1.h
 *
 * Timer1 Driver .h file (Header file)
 *      Author: hnelamir
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"

/*                    Types                     */
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;

typedef enum{
		Normal=0,CTC=0x04
}Timer1_Mode;


typedef struct{
	uint16 initial_value;
	uint16 compare_value;//compare mode only
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
}Timer1_ConfigType;





/*                    Prototypes                     */

/* To initialize the Timer */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/* To disable The Timer */
void Timer1_deInit(void);

/* To set the call back function address*/
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
