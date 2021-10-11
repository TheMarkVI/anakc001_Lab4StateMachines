/*	Author: Artip Nakchinda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: 
 *          - Household digital combination lock
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, wait, key1_press, key1_rel, key2_press, unlock, lock}state;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;

    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}

void Tick() {
    // start, wait, key1_press, key1_rel, key2_press, unlock, lock

    switch(state) { // transitions
        case start:
            state = wait;
        case wait:
            if(PINA == 0x04) 
                state = key1_press;
            else if(PINA == 0x80)
                state = lock;
            else 
                state = wait;
            break;
        case key1_press:
            if(PINA == 0x04)
                state = key1_press;
            else if(PINA == 0x00)
                state = key1_rel;
            else 
                state = wait;
            break;
        case key1_rel:
            if(PINA == 0x00)
                state = key1_rel;
            else if(PINA == 0x02)
                state = key2_press;
            else
                state = wait;
            break;
        case key2_press:
            if(PINA == 0x02)
                state = key2_press;
            else if(PINA == 0x00)
                state = unlock;
            else
                state = wait;
            break;
        case unlock:
            if(PINA == 0x00)
                state = unlock;
            else if(PINA == 0x80)
                state = lock;
            break;
        case lock:
            if(PINA == 0x80)
                state = lock;
            else
                state = wait;
            break;
    }

    switch(state) { // state actions
        case start:
        case wait:
            PORTB = 0x00;
            break;
        case key1_press:
            break;
        case key1_rel:
            break;
        case key2_press:
            PORTB = 0x01;
            break;
        case unlock:
            PORTB = 0x01;
            break;
        case lock:
            PORTB = 0x00;
            break;
    }

    PORTC = state;
}
