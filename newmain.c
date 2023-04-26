/* 
 * File:   newmain.c
 * Author: xiaogan zhang 
 * id : 1596973
 *
 * Created on October 24, 2021, 7:08 PM
 */
#define F_CPU 1000000
#include <stdio.h>
#include <stdlib.h>
#include<avr/io.h>
#include <util/delay.h>

/*
 * 
 */
void music(int rhythm1, int rhythm2, int Time ){

    music1(rhythm1) ;  // timer1 
    music2(rhythm2) ;// timer2
    duration(Time);

}

void music1( ){

    TCCR0A = 0x40; // CTC mode
    TCCR0B = 0x0A;
    OCR1A = 24999;
}

void music2( ){

    TCCR1A = 0x40; 
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);// CTC mode
    OCR0A = 40000;
}

void duration( int time){
    if (time == 100){
    _delay_ms(100);
    };
}


int main(void) {
    DDRD &= (1<<DDD6); // make PD6 as input 
    PIND |= (1<<PIND6);// input    1 to PD6
    
    PORTB &=~(1<< PORTB2); // PB2 as a output to the buzzer 
    DDRB |= (1<<DDB2);
    PORTB &=~(1<<PORTB3);// output for PB3 to the buzzer
    DDRB |= (1<<DDB3);
    
    
    while(1) {
        
        if ((PIND & (1<< PIND6 ))==0){
            PIND |= (1<<PIND6);
            
            while(1){
                music(175,94,100);
                music(126,62,100);
                music(189,94,100);
                music(189,94,100);
                music(126,62,100); 
                music(171,94,100);
            
            
            
            }
        
        }
    
    
    
    
    
    
    
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return (0);
}

