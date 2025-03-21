/*
 * timer1.c
 *
 *  Timer1 Driver .c file (Source file)
 *      Author: hnelamir
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
#include "gpio.h"
#include "timer1.h"

/*                    Global Variables                     */
static volatile void(*g_callBackPtr)(void)= NULL_Ptr;

/*                       ISR                               */
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr!=NULL_Ptr){
		(*g_callBackPtr)();
	}
}


ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr!=NULL_Ptr){
		(*g_callBackPtr)();
	}
}


/*                       Functions                        */

/* To initialize the Timer */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCNT1=Config_Ptr->initial_value;
	SREG|=(1<<7);
	TCCR1A=(1<<COM1A1)|(1<<FOC1A)|(1<<FOC1B);
	TCCR1B=(TCCR1B&0xF8)|(Config_Ptr->prescaler);

	switch(Config_Ptr->mode){
		case Normal:
			TCCR1A=(TCCR1A|0xFC)|(Config_Ptr->mode);
			TIMSK|=(1<<TOIE1);
			break;
		case CTC:
			GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
			TCCR1B=(TCCR1B&0xE7)|((Config_Ptr->mode)<<1);
			TIMSK|=(1<<OCIE1A);
			OCR1A=Config_Ptr->compare_value;
			break;
	}

}
/* To disable The Timer */
void Timer1_deInit(void){
	TIMSK&=~(1<<TOIE1);
	TIMSK&=(1<<OCIE1A);
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
}
/* To set the call back function address*/
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}

