
/*	Author: basi001
 *  Partner(s) Name: chris hyunh
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif



enum SM_States {Begin, Init, Wait, Add, Minus, Reset} SM_State;

//global
unsigned char tmpC = 0x00;
#define inputs (~PINB & 0x03)

void Abbacus()
{
	switch(SM_State){
		case Begin:
			tmpC = 0x00;
			SM_State = Init;
			break;
		case Init:
			if(inputs == 0x01) {
				SM_State = Add;
				break;
			} else if(inputs == 0x02) {
				SM_State = Minus;
				break;	
			} else if(inputs == 0x03) {
				SM_State = Reset;
				break;
			} else {
				SM_State = Init;
				break;
			}
		case Add:
			SM_State = Wait;
			break;
		case Minus:
			SM_State = Wait;
			break;
		case Reset:
			if((inputs == 0x01) || (inputs == 0x02)) {
				SM_State = Reset;
				break;
			} else {
				SM_State = Init;
				break;
			}
		case Wait:
			if((inputs == 0x01) || (inputs == 0x02)) {
				SM_State = Wait;
				break;
			} else {
				SM_State = Init;
				break;
			}
		default:
			break;
	}
	
	switch(SM_State){
		case Begin:
		case Init:
		case Wait:
			break;
		case Add:
			if(tmpC >= 0x09){
				tmpC = tmpC;
				break;

			} else {
				tmpC = tmpC + 0x01;
				break;
			}
		case Minus:
			if(tmpC <= 0x00){
				tmpC = tmpC;
				break;
			} else {
				tmpC = tmpC - 0x01;
				break;
			}
		case Reset:
			tmpC = 0x00;
			break;
	}
	PORTC = tmpC;
}
		

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	SM_State = Begin;
    /* Insert your solution below */
    while (1) {
	Abbacus();
    }
    return 1;
}

