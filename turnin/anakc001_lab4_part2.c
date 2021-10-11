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

enum States{start, wait, reset, increment, incrementWait, decrement, decrementWait}state;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */

    state = start;

    while (1) {
        Tick();
    }
    return 1;
}

void Tick() {
    switch(state) { // transitions
        case start:
            state = wait;
            PORTC = 7;
            break;
        case wait:
            if(PINA == 0x03)
                state = reset;
            else if(PINA == 0x01)
                state = increment;
            else if(PINA == 0x02)
                state = decrement;
            break;
        case reset:
            if(PINA == 0x03)
                state = reset;
            else
                state = wait;
            break;
        case increment:
        case incrementWait:
            if(PINA == 0x03)
                state = reset;
            else if(PINA == 0x01)
                state = incrementWait;
            else
                state = wait;            
            break;
        case decrement:
        case decrementWait:
            if(PINA == 0x03)
                state = reset;
            else if(PINA == 0x02) 
                state = decrementWait;
            else
                state = wait;
            break;
    }

    switch(state) { // state actions
        case start:
            break;
        case wait:
            break;
        case reset:
            PORTC = 0x00;
            break;
        case increment:
            if(PORTC != 0x09)
            PORTC += 0x01;
        case incrementWait:
            break;
        case decrement:
            if(PORTC != 0x00)
               PORTC -= 0x01;
            break;
        case decrementWait:
            break;
    }


}
