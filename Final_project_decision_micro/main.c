#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "eeprom.h"
#include "i2c.h"
#include "motor.h"
#include "TIMER.h"
#include "uart.h"
/*------------------------------------------Global Variables------------------------------------ */
uint8 status;/*status of the lock*/
uint8 READY=0x10;/*ready byte to be sent and recieved*/
uint8 status_READY=0x20;
uint8 matched=0x30;
uint8 unmatched=0x40;
uint8 thief=0x50;
uint8 result_READY=0x60;
uint8 count=0;/*each count= 5 seconds*/
uint8 Timer_finish=0;/*required timing finished*/

/*-----------------------------------------Functions Prototypes-----------------------------------*/

void Timer_add_count(void);
void Timer_count(uint8 time_5seconds);
void Save_Password(const uint8 * pass);
uint8 Compare_Password(const uint8 * pass);
void get_password(uint8 *pass);
void open_door(void);
void Theif(void);


/*------------------------------------------Main Function--------------------------------------*/


int main(void){
	struct TIMER_init Timer2;
	uint8 failed=0;
	uint8 pass[5];

	UART_config config = {BIT_8, DISABLE, STOP_BIT_1};   // 8_bit frame, parity disabled, 1 stop bit
	uart_init(&config);

	Timer2.timer=1;
	Timer2.mode=1;
	Timer2.comp_value=39062;
	Timer2.prescaler=1024;
	Timer2.comp_match_mode=0;
	SREG|=(1<<7);
	TIMER_Init(&Timer2);
	TIMER_Stop(1);
	TIMER_Timer1SetCallBack(&Timer_add_count);
	EEPROM_init();
	DDRD|=(1<<7);
	MOTOR_init();


	get_password(pass);
	Save_Password(pass);


	while(1){
		while(UART_RecieveByte()!=status_READY){};
		UART_SendByte(status_READY);
		status=UART_RecieveByte();
		if(status=='+')
		{
			get_password(pass);
			failed=Compare_Password(pass);
			if(failed==0)
			{
				UART_SendByte(result_READY);
				while(UART_RecieveByte()!=result_READY){};
				UART_SendByte(matched);
				get_password(pass);
				Save_Password(pass);
			}
			else{
				UART_SendByte(result_READY);
				while(UART_RecieveByte()!=result_READY){};
				UART_SendByte(unmatched);
				get_password(pass);
				failed=Compare_Password(pass);
				if(failed==0)
				{
					UART_SendByte(result_READY);
					while(UART_RecieveByte()!=result_READY){};
					UART_SendByte(matched);
					get_password(pass);
					Save_Password(pass);
				}
				else{
					UART_SendByte(result_READY);
					while(UART_RecieveByte()!=result_READY){};
					UART_SendByte(unmatched);
					get_password(pass);
					failed=Compare_Password(pass);
					if(failed==0)
					{
						UART_SendByte(result_READY);
						while(UART_RecieveByte()!=result_READY){};
						UART_SendByte(matched);
						get_password(pass);
						Save_Password(pass);
					}
					else{
						UART_SendByte(result_READY);
						while(UART_RecieveByte()!=result_READY){};
						UART_SendByte(thief);
						Theif();
						}
					}
				}
		}else if(status=='-')
		{
			get_password(pass);
			failed=Compare_Password(pass);
			if(failed==0)
			{
				UART_SendByte(result_READY);
				while(UART_RecieveByte()!=result_READY){};
				UART_SendByte(matched);
				open_door();

			}
			else{
				UART_SendByte(result_READY);
				while(UART_RecieveByte()!=result_READY){};
				UART_SendByte(unmatched);
				get_password(pass);
				failed=Compare_Password(pass);
				if(failed==0)
				{
					UART_SendByte(result_READY);
					while(UART_RecieveByte()!=result_READY){};
					UART_SendByte(matched);
					open_door();
				}
				else{
					UART_SendByte(result_READY);
					while(UART_RecieveByte()!=result_READY){};
					UART_SendByte(unmatched);
					get_password(pass);
					failed=Compare_Password(pass);
					if(failed==0)
					{
						UART_SendByte(result_READY);
						while(UART_RecieveByte()!=result_READY){};
						UART_SendByte(matched);
						open_door();
					}
					else{
						UART_SendByte(result_READY);
						while(UART_RecieveByte()!=result_READY){};
						UART_SendByte(thief);
						Theif();

						}
					}
				}
		}

	}



/*--------------------------------------------Functions----------------------------------------*/



	return 0;
}





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

void get_password(uint8 *pass){
	uint8 i;
	while(UART_RecieveByte()!=READY){};
	for(i=0;i<5;i++){
		UART_SendByte(READY);
		pass[i]=UART_RecieveByte();
	}
}

void Save_Password(const uint8 * pass){
	uint8 i;
	for(i=0;i<5;i++){
		EEPROM_writeByte((0x000 | i),pass[i]);
		_delay_ms(20);
	}
}

uint8 Compare_Password(const uint8 * pass){
	uint8 i,EEPROM_read;
	for(i=0;i<5;i++){
		EEPROM_readByte((0x000 | i),&EEPROM_read);
		_delay_ms(20);
		if(pass[i]!=EEPROM_read)
			return 1;
	}
	return 0;
}

void open_door(void){
	MOTOR_clockwise();
	Timer_count(2);
	Timer_finish=0;
	MOTOR_anticlockwise();
	Timer_count(2);
	Timer_finish=0;
	MOTOR_stop();
}

void Theif(void){
	PORTD|=(1<<7);
	Timer_count(12);
	PORTD&=(~(1<<7));
}

