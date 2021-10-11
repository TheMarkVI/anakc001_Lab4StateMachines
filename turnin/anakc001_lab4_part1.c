/*	Author: Artip Nakchinda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: 
 *      - PB0 and PB1 connected to an LED
 *      - Press a button (PA0) switches between the two LEDs
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, ledRel1, ledPress1, ledRel2, ledPress2}state;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}

void Tick() {
    switch(state) { // Transitions
        case start: 
            state = ledRel1;
            break;

        case ledRel1:
            if((PINA & 0x01) == 1) {
                state = ledPress1;
            }
            else {
                state = ledRel1;
            }
            break;
        
        case ledPress1:
            if((PINA & 0x01) == 1) {
                state = ledPress1;
            }
            else {
                state = ledRel2;
            }
            break;
        case ledRel2:
            if((PINA & 0x01) == 1) {
                state = ledPress2;
            }
            else {
                state = ledRel2;
            }
            break;

        case ledPress2:
            if((PINA & 0x01) == 1) {
                state = ledPress2;
            }
            else {
                state = ledRel1;
            }
        
    }

    switch(state) { // State Actions 
        case start:
            PORTB = 0x01;
            break;
        
        case ledRel1:
            PORTB = 0x01;
            break;

        case ledPress1:
        case ledRel2:
            PORTB = 0x02;
            break;

        case ledPress2:
            PORTB = 0x01;
            break;

    }
}
