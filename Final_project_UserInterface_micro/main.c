#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "lcd.h"
#include "TIMER.h"
#include "uart.h"
#include "keypad.h"

/*------------------------------------------Global Variables------------------------------------ */
uint8 status;/*status of the lock*/
uint8 count=0;/*each count= 5 seconds*/
uint8 Timer_finish=0;/*required timing finished*/
uint8 READY=0x10;/*ready byte to be sent and received*/
uint8 status_READY=0x20;
uint8 matched=0x30;
uint8 unmatched=0x40;
uint8 thief=0x50;
uint8 result_READY=0x60;

/*-----------------------------------------Functions Prototypes-----------------------------------*/

void Timer_add_count(void);
void Timer_count(uint8 time_5seconds);
void get_password(uint8* str);
void send_password(uint8* str);
/*------------------------------------------Main Function--------------------------------------*/
int main(void){

	struct TIMER_init Timer1;
	uint8 pass_1[5];
	uint8 pass_2[5];
	uint8 match=1,i;
	uint8 option,result;
	uint8 retry=0;
	UART_config config = {BIT_8, DISABLE, STOP_BIT_1};   // 8_bit frame, parity disabled, 1 stop bit
	uart_init(&config);
	Timer1.timer=1;
	Timer1.mode=1;
	Timer1.comp_value=39062;
	Timer1.prescaler=1024;
	Timer1.comp_match_mode=0;
	SREG|=(1<<7);
	TIMER_Init(&Timer1);
	TIMER_Stop(1);
	TIMER_Timer1SetCallBack(&Timer_add_count);
	LCD_init();
	LCD_displayStringRowColumn(0,0,"HELLO");
	_delay_ms(500);
	LCD_clearScreen();
	do{
		match=1;
		LCD_displayStringRowColumn(0,0,"ENTER NEW PASS");
		LCD_goToRowColumn(1,0);
		get_password(pass_1);
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"reenter pass");
		LCD_goToRowColumn(1,0);
		get_password(pass_2);
		LCD_clearScreen();
		for(i=0;i<5;i++){
			if(pass_1[i]!=pass_2[i])
				match=0;
		}
	}while(!match);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"password match");
	_delay_ms(1000);
	send_password(pass_1);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Password saved");
	_delay_ms(1000);

	while(1){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"+: change password");
		LCD_displayStringRowColumn(1,0,"-: open door");
		option=KeyPad_getPressedKey();
		_delay_ms(500);
		if(option=='+')
		{
			do{LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Enter password");
			LCD_goToRowColumn(1,0);
			get_password(pass_1);
			if(retry==0){
				UART_SendByte(status_READY);
			while(UART_RecieveByte()!=status_READY){};
			UART_SendByte(option);
			}
			send_password(pass_1);
			while(UART_RecieveByte()!=result_READY){};
			UART_SendByte(result_READY);
			result=UART_RecieveByte();
			retry++;
			}while(result==unmatched);

			if(result==matched){
				LCD_clearScreen();
				do{
					LCD_displayStringRowColumn(0,0,"ENTER NEW PASS");
					LCD_goToRowColumn(1,0);
					get_password(pass_1);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"reenter pass");
					LCD_goToRowColumn(1,0);
					get_password(pass_2);
					for(i=0;i<5;i++){
						if(pass_1[i]!=pass_2[i])
							match=0;
					}
				}while(match==0);
				send_password(pass_1);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Password saved");

			}
			else if(result==thief){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Emsek 7aramy");
				LCD_displayStringRowColumn(1,0,"Calling 122");
				Timer_count(12);
				Timer_finish=0;
			}
			retry=0;
		}
		else if(option=='-'){

			do{LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Enter password");
			LCD_goToRowColumn(1,0);
			get_password(pass_1);
			if(retry==0){
				UART_SendByte(status_READY);
			while(UART_RecieveByte()!=status_READY){};
			UART_SendByte(option);
			}

			send_password(pass_1);
			while(UART_RecieveByte()!=result_READY){};
			UART_SendByte(result_READY);
			result=UART_RecieveByte();
			retry++;
			}while(result==unmatched);

			if(result==matched){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Door unlocking");
				Timer_count(2);
				Timer_finish=0;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Door locking");
				Timer_count(2);
				Timer_finish=0;
			}
			else if(result==thief){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Emsek 7aramy");
				LCD_displayStringRowColumn(1,0,"Calling 122");
				Timer_count(12);
				Timer_finish=0;
			}
			retry=0;
		}

	}



	return 0;
}


/*--------------------------------------------Functions----------------------------------------*/



void Timer_add_count(void){
	count++;
}


void Timer_count(uint8 time_5seconds){
	count=0;
	TIMER_Start(1,1024);
	while(count!= time_5seconds){};
	Timer_finish=1;
	TIMER_Stop(1);
}

void get_password(uint8* str){
	uint8 i=0;
	for(i=0;i<5;i++){

		str[i]=KeyPad_getPressedKey();
		_delay_ms(400);
		LCD_displayCharacter('*');

	}


}

void send_password(uint8* str){
	uint8 i=0;
	_delay_ms(50);
	UART_SendByte(READY);
	for(i=0;i<5;i++){
		while(UART_RecieveByte()!=READY){};
		UART_SendByte(str[i]);

	}
}




