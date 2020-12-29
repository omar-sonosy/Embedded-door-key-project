/*
 * TIMER.c
 *
 *  Created on: 8/10/2020
 *      Author: Omar Hany
 */

#include "TIMER.h"

static volatile void(*timer0)(void)= NULL;
static volatile void(*timer1)(void)= NULL;
static volatile void(*timer2)(void)= NULL;

void TIMER_Init(struct TIMER_init *i){
	if(i->timer==0){
		SET_BIT(TCCR0,FOC0);
		OCR0 = i->comp_value;
		//timer mode
		if(i->mode==0){
			CLEAR_BIT(TCCR0,WGM01);
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TIMSK,TOIE0);

		}
		else if(i->mode==1){
			SET_BIT(TCCR0,WGM01);
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TIMSK,OCIE0);
		}

		// clock select
		if(i->prescaler==1){
			CLEAR_BIT(TCCR0,CS02);
			CLEAR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS00);
		}
		else if(i->prescaler==8){
			CLEAR_BIT(TCCR0,CS02);
			SET_BIT(TCCR0,CS01);
			CLEAR_BIT(TCCR0,CS00);
		}
		else if(i->prescaler==64){
			CLEAR_BIT(TCCR0,CS02);
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS00);
		}
		else if(i->prescaler==256){
			SET_BIT(TCCR0,CS02);
			CLEAR_BIT(TCCR0,CS01);
			CLEAR_BIT(TCCR0,CS00);
		}
		else if(i->prescaler==1024){
			SET_BIT(TCCR0,CS02);
			CLEAR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS00);
		}

		// compare match output mode
		if(i->comp_match_mode==0){
			CLEAR_BIT(TCCR0,COM01);
			CLEAR_BIT(TCCR0,COM00);
		}
		else if(i->comp_match_mode==1){
			SET_BIT(DDRB,PB3);
			CLEAR_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
		else if(i->comp_match_mode==2){
			SET_BIT(DDRB,PB3);
			SET_BIT(TCCR0,COM01);
			CLEAR_BIT(TCCR0,COM00);
		}
		else if(i->comp_match_mode==3){
			SET_BIT(DDRB,PB3);
			SET_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}


	}
	else if(i->timer==1){
		SET_BIT(TCCR1A,FOC1A);
		OCR1A= i->comp_value;
		//timer mode
		if(i->mode==0){
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			SET_BIT(TIMSK,TOIE1);

		}
		else if(i->mode==1){
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			SET_BIT(TIMSK,OCIE1A);
		}

		// clock select
		if(i->prescaler==1){
			CLEAR_BIT(TCCR1B,CS12);
			CLEAR_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==8){
			CLEAR_BIT(TCCR1B,CS12);
			SET_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==64){
			CLEAR_BIT(TCCR1B,CS12);
			SET_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==256){
			SET_BIT(TCCR1B,CS12);
			CLEAR_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==1024){
			SET_BIT(TCCR1B,CS12);
			CLEAR_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS10);
		}

		// compare match output mode
		if(i->comp_match_mode==0){
			CLEAR_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
		}
		else if(i->comp_match_mode==1){
			SET_BIT(DDRD,PD5);
			CLEAR_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
		}
		else if(i->comp_match_mode==2){
			SET_BIT(DDRD,PD5);
			SET_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
		}
		else if(i->comp_match_mode==3){
			SET_BIT(DDRD,PD5);
			SET_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
		}


	}
	else if(i->timer==2){
		SET_BIT(TCCR2,FOC2);
		OCR2 = i->comp_value;
		//timer mode
		if(i->mode==0){
			CLEAR_BIT(TCCR2,WGM21);
			CLEAR_BIT(TCCR2,WGM20);
			SET_BIT(TIMSK,TOIE2);

		}
		else if(i->mode==1){
			SET_BIT(TCCR2,WGM21);
			CLEAR_BIT(TCCR2,WGM20);
			SET_BIT(TIMSK,OCIE2);
		}

		// clock select
		if(i->prescaler==1){
			CLEAR_BIT(TCCR2,CS22);
			CLEAR_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS20);
		}
		else if(i->prescaler==8){
			CLEAR_BIT(TCCR2,CS22);
			SET_BIT(TCCR0,CS21);
			CLEAR_BIT(TCCR2,CS20);
		}
		else if(i->prescaler == 32){
			CLEAR_BIT(TCCR2,CS22);
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS20);
		}
		else if(i->prescaler==64){
			SET_BIT(TCCR2,CS22);
			CLEAR_BIT(TCCR2,CS21);
			CLEAR_BIT(TCCR2,CS20);
		}
		else if(i->prescaler==128){
			SET_BIT(TCCR2,CS22);
			CLEAR_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS20);
		}
		else if(i->prescaler==256){
			SET_BIT(TCCR2,CS22);
			SET_BIT(TCCR2,CS21);
			CLEAR_BIT(TCCR2,CS20);
		}
		else if(i->prescaler==1024){
			SET_BIT(TCCR2,CS22);
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS20);
		}

		// compare match output mode
		if(i->comp_match_mode==0){
			CLEAR_BIT(TCCR2,COM21);
			CLEAR_BIT(TCCR2,COM20);
		}
		else if(i->comp_match_mode==1){
			SET_BIT(DDRD,PD7);
			CLEAR_BIT(TCCR2,COM21);
			SET_BIT(TCCR2,COM20);
		}
		else if(i->comp_match_mode==2){
			SET_BIT(DDRD,PD7);
			SET_BIT(TCCR2,COM21);
			CLEAR_BIT(TCCR2,COM20);
		}
		else if(i->comp_match_mode==3){
			SET_BIT(DDRD,PD7);
			SET_BIT(TCCR2,COM21);
			SET_BIT(TCCR2,COM20);
		}


	}




}
void TIMER_Start(uint8 t , uint16 clk){




		if(t==0){

			// clock select
			if(clk==1){
				CLEAR_BIT(TCCR0,CS02);
				CLEAR_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS00);
			}
			else if(clk==8){
				CLEAR_BIT(TCCR0,CS02);
				SET_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS00);
			}
			else if(clk==64){
				CLEAR_BIT(TCCR0,CS02);
				SET_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS00);
			}
			else if(clk==256){
				SET_BIT(TCCR0,CS02);
				CLEAR_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS00);
			}
			else if(clk==1024){
				SET_BIT(TCCR0,CS02);
				CLEAR_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS00);
			}

		}
		else if(t==1){

			// clock select
			if(clk==1){
				CLEAR_BIT(TCCR1B,CS12);
				CLEAR_BIT(TCCR1B,CS11);
				SET_BIT(TCCR1B,CS10);
			}
			else if(clk==8){
				CLEAR_BIT(TCCR1B,CS12);
				SET_BIT(TCCR1B,CS11);
				CLEAR_BIT(TCCR1B,CS10);
			}
			else if(clk==64){
				CLEAR_BIT(TCCR1B,CS12);
				SET_BIT(TCCR1B,CS11);
				SET_BIT(TCCR1B,CS10);
			}
			else if(clk==256){
				SET_BIT(TCCR1B,CS12);
				CLEAR_BIT(TCCR1B,CS11);
				CLEAR_BIT(TCCR1B,CS10);
			}
			else if(clk==1024){
				SET_BIT(TCCR1B,CS12);
				CLEAR_BIT(TCCR1B,CS11);
				SET_BIT(TCCR1B,CS10);
			}




		}
		else if(t==2){


			// clock select
			if(clk==1){
				CLEAR_BIT(TCCR2,CS22);
				CLEAR_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS20);
			}
			else if(clk==8){
				CLEAR_BIT(TCCR2,CS22);
				SET_BIT(TCCR0,CS21);
				CLEAR_BIT(TCCR2,CS20);
			}
			else if(clk == 32){
				CLEAR_BIT(TCCR2,CS22);
				SET_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS20);
			}
			else if(clk==64){
				SET_BIT(TCCR2,CS22);
				CLEAR_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS20);
			}
			else if(clk==128){
				SET_BIT(TCCR2,CS22);
				CLEAR_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS20);
			}
			else if(clk==256){
				SET_BIT(TCCR2,CS22);
				SET_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS20);
			}
			else if(clk==1024){
				SET_BIT(TCCR2,CS22);
				SET_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS20);
			}



		}



}
void TIMER_Stop(uint8 t){
	if(t==0){
			// clock select
		CLEAR_BIT(TCCR0,CS02);
		CLEAR_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS00);


	}
	else if(t==1){
	// clock select
		CLEAR_BIT(TCCR1B,CS12);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS10);
	}
	else if(t==2){
	// clock select
		CLEAR_BIT(TCCR2,CS22);
		CLEAR_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS20);
	}

}

void TIMER_Timer0SetCallBack(void(*ptr)(void)){
	timer0 = ptr;
}
void TIMER_Timer1SetCallBack(void(*ptr)(void)){
	timer1=ptr;
}
void TIMER_Timer2SetCallBack(void(*ptr)(void)){
	timer2=ptr;
}

ISR(TIMER0_COMP_vect){
	if(timer0!= NULL){
		(*timer0)();
	}
}
ISR(TIMER1_COMPA_vect){
	if(timer1!= NULL){
		(*timer1)();
	}
}
ISR(TIMER2_COMP_vect){
	if(timer2!= NULL){
		(*timer2)();
	}
}
ISR(TIMER0_OVF_vect){
	if(timer0!= NULL){
		(*timer0)();
	}
}
ISR(TIMER1_OVF_vect){
	if(timer1!= NULL){
		(*timer1)();
	}
}
ISR(TIMER2_OVF_vect){
	if(timer2!= NULL){
		(*timer2)();
	}
}
