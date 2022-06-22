/*
 * Prac_6.c
 *
 * Created: 6/15/2022 8:19:30 AM
 * Author : Vishva
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define button PD2
int VALUE=1;

uint8_t var = 0;
char clkstep[]={0x09, 0x0C, 0x06, 0x03}; //full step hex numbers 90 degree clockwise
char aclkstep[]={0x09, 0x03, 0x06, 0x0C}; //full step hex numbers 90 degree counterclockwise

void init(){
	DDRC |= 0x0f; // lower bits of PORTC declared as outputs
	DDRB = 0x00; // B ports for input pin
}


void init_interrupt(){
	DDRD &= ~(1<<PIND2); //INT0 as an input
	EIMSK |= 0b00000001; //Enable External Interrupts INT0
	EICRA |= 0b00000010; //falling edge
	sei(); // setting global interrupt enable bit in SREG
}
ISR (INT0_vect) //External interrupt_zero ISR
{
			if(VALUE==1){VALUE=0;}else{VALUE=1;}
	
}


int main(void)
{
	init();
	while (1)
	{
		init_interrupt();
		if(VALUE==1){
			
			for (uint8_t j=0;j<4;j++){
				PORTC = clkstep[j]; //Rotation clockwise
			_delay_ms(100);}
		}
		
		if(VALUE==0){
			for (uint8_t k=0;k<4;k++){
				PORTC = aclkstep[k]; //Rotation anticlockwise
				_delay_ms(100);
			}
		
		}
	}
}

