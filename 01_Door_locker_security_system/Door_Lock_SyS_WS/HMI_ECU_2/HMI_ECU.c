 /*
 * HMI_ECU.c
 *
 *  HMI_ECU Source File
 *      Author: hnelamir
 */

#include <avr/io.h>
#include <util/delay.h>
#include "std_types.h"
#include "uart.h"
#include "timer1.h"
#include "keypad.h"
#include "lcd.h"
#define SUCCESS 1
#define FAILED 0



/*                     Global variables                       */

uint8 g_HMI_ticks=0;
uint8 g_check=0;
uint8 g_counter=0;
uint8 g_Pass_Check=0;

/*                     Functions                              */



void First_Pass(){
	uint8 F_pass=-1,i=0;
	LCD_clearScreen();
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1,0);
	UART_sendByte('F');
	for(i=0;i<5;i++){
		F_pass=KEYPAD_getPressedKey();
		if ((F_pass<=9)&&(F_pass>=0)){
			LCD_displayCharacter('*');
			UART_sendByte(F_pass);

		}
		else
			i--;
	_delay_ms(500);
	}
	F_pass=KEYPAD_getPressedKey();
	if(F_pass=='='){
		LCD_clearScreen();
		LCD_displayString("plz re-enter the");
		LCD_moveCursor(1,0);
		LCD_displayString("same pass:");
		UART_sendByte(F_pass);
	}
	LCD_moveCursor(1,11);

	for(i=0;i<5;i++){
			F_pass=KEYPAD_getPressedKey();
			if ((F_pass<=9)&&(F_pass>=0)){
				LCD_displayCharacter('*');
				UART_sendByte(F_pass);
				_delay_ms(10);

			}
			else
				i--;
		_delay_ms(500);
		}
	F_pass=KEYPAD_getPressedKey();
	if(F_pass=='='){
		UART_sendByte('=');

	}
	g_check=UART_recieveByte();
	if(g_check){
		LCD_clearScreen();
	}
	else {
		LCD_clearScreen();
		First_Pass();}


}


void Buzzer_HMI(){
	LCD_clearScreen();
	UART_sendByte('B');
	LCD_displayString("ERROR");
	g_HMI_ticks=0;
	while(g_HMI_ticks<=60);
	g_HMI_ticks=0;
}
void Password(){
	uint8 i=0,F_pass=-1;
		LCD_clearScreen();
		UART_sendByte('C');
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);
			for(i=0;i<5;i++){
				F_pass=KEYPAD_getPressedKey();
				if ((F_pass<=9)&&(F_pass>=0)){
					LCD_displayCharacter('*');
					UART_sendByte(F_pass);

				}
				else
					i--;
			_delay_ms(500);
			}
		F_pass=KEYPAD_getPressedKey();
		if(F_pass=='='){
			LCD_clearScreen();
		}
		g_Pass_Check=UART_recieveByte();
}

void Change_Pass(){
	Password();
	if(g_Pass_Check==FAILED){
		g_counter++;
		if(g_counter==3){
			Buzzer_HMI();
			LCD_clearScreen();
			g_counter=0;
			return ;
					}
		else{
			Change_Pass();
				}
		}
	else{
		g_counter=0;
		First_Pass();

	}

}

void Door_Control(){
	Password();
		if(g_Pass_Check==FAILED){
			g_counter++;
			if(g_counter==3){
				Buzzer_HMI();
				LCD_clearScreen();
				g_counter=0;
				return ;
						}
			else{
				Change_Pass();
					}
			}
		else{
			g_counter=0;
			UART_sendByte('O');
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Door is");
			LCD_displayStringRowColumn(1, 0, "Unlocking");
			g_HMI_ticks = 0;
			while (g_HMI_ticks<= 15);
			while (g_HMI_ticks <= 18);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Door is");
			LCD_displayStringRowColumn(1, 0, "Locking");
			while (g_HMI_ticks <= 33);
			g_HMI_ticks = 0;

		}
}
void HMI_Ticks(){
	g_HMI_ticks++;
}

/*                     Main Function                          */

int main(void){
	uint8 Input;
	/* Timer1 initial setup
	 *  Initial Value=0
	 *  Compare Value=999
	 *  Prescaler = 1024
	 *  Mode = CTC (Compare)
	 */
	Timer1_ConfigType TimConfig_HMI={0,31249,F_CPU_256,CTC};
	Timer1_init(&TimConfig_HMI);
	/* UART frame Setup
	 * 	Date Length=8
	 * 	Parity type=Even
	 * 	Stop Bits=1
	 * 	Baudrate=9600
	 */
	UART_ConfigType UARTConfig_HMI={EIGHT,EVEN,ONE_BIT,BR7};
	UART_init(&UARTConfig_HMI);
	Timer1_setCallBack(HMI_Ticks);
	LCD_init();
	First_Pass();

	while(1){
		LCD_clearScreen();
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1,0);
		LCD_displayString("- : Change Pass");
		Input=KEYPAD_getPressedKey();
		switch(Input){
		case '+':
			Door_Control();
			break;
		case '-':
			g_counter=0;
			Change_Pass();
			break;
		}
	}

}
