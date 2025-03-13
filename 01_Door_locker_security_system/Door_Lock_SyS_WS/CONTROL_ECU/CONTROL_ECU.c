/*
 * CONTROL_ECU.c
 *
 *  CONTROL_ECU main file
 *      Author: hnelamir
 */


#include <avr/io.h>
#include <util/delay.h>
#include "dc_motor.h"
#include "external_eeprom.h"
#include "timer1.h"
#include "uart.h"
#include "buzzer.h"
#include "twi.h"
#define SUCCESS 1
#define FAILED 0
/*                     Global variables                       */
uint8 g_statue=0;
uint8 g_ECU_ticks=0;
uint8 g_count=0;



/*                     Functions                              */


void First_Save(){
	uint8 key1[5]={0},key2[5]={0},i,y,check=0;
	for (i=0;i<5;i++){
		key1[i]=UART_recieveByte();
	}
	if(UART_recieveByte()=='='){
		for (y=0;y<5;y++){
				key2[y]=UART_recieveByte();
			}}
	if(UART_recieveByte()=='='){
		check=0;
		for(i=0;i<5;i++){
			if(key1[i]==key2[i]){
			check++;
			}
		}
	}
	if(check==5){
		for(i=0;i<5;i++){
			_delay_ms(20);
			g_statue=EEPROM_writeByte((0x00FF+i),key1[i]);
		}
			if(g_statue==SUCCESS){
				UART_sendByte(SUCCESS);}
			else{
				UART_sendByte(FAILED);}
		}

	else{
			UART_sendByte(FAILED);

			}

	check=0;
}
void Buzzer_ECU(){
	g_ECU_ticks = 0;
	Buzzer_on();
	while (g_ECU_ticks <= 60);
	g_ECU_ticks = 0;
	Buzzer_off();
}

void Check_Pass(){
	uint8 read,temp;

		for(int i=0;i<5;i++)
		{
			_delay_ms(10);
			EEPROM_readByte((0x00FF)+i, &read);
			temp=UART_recieveByte();
			if(read!=temp){
				g_statue=FAILED;
			}
		}
		UART_sendByte(g_statue);
		/*if(g_statue==SUCCESS)
		{
			g_count=0;
			First_Save();
		}
		else
		{
			g_count++;
			if(g_count==3)
			{
				g_count=0;
				Buzzer_ECU();
			}
			else
			{
				Check_Pass();
			}

		}*/}

void ECU_Ticks(){
	g_ECU_ticks++;
}


/*                     Main Function                          */
int main(void){
		uint8 HMI_recived;
		/* Timer1 initial setup
		 *  Initial Value=0
		 *  Compare Value=31249
		 *  Prescaler = 256
		 *  Mode = CTC (Compare)
		 */
		Timer1_ConfigType TimConfg_ECU={0,31249,F_CPU_256,CTC};
		Timer1_init(&TimConfg_ECU);
		/* UART frame Setup
		 * 	Date Length=8
		 * 	Parity type=Even
		 * 	Stop Bits=1
		 * 	Baudrate=9600
		 */
		UART_ConfigType UARTConfig_ECU={EIGHT,EVEN,ONE_BIT,BR7};
		UART_init(&UARTConfig_ECU);

		/*TWI setup for eeprom
		 * Adress=00000010
		 *Bit rate=400Kbs */

		TWI_ConfigType twiConfig={0b00000010,400000};
		TWI_init(&twiConfig);
		Timer1_setCallBack(ECU_Ticks);
		DCMotor_init();
		Buzzer_init();
		while(1){
			HMI_recived=UART_recieveByte();
			switch (HMI_recived){
			case 'F':
				First_Save();
				break;
			case 'C':
				Check_Pass();
				break;
			case 'B':
				Buzzer_ECU();
				break;
			case 'O':
				DCMotor_Rotate(CLOCKWISE, 100);
				g_ECU_ticks = 0;
				while (g_ECU_ticks <= 15);
				DCMotor_Rotate(STOP, 0);
				while (g_ECU_ticks <= 18);
				DCMotor_Rotate(ANTI_CLOCKWISE, 100);
				while (g_ECU_ticks <= 33);
				g_ECU_ticks = 0;
				DCMotor_Rotate(STOP, 0);
			}
			}

		}


