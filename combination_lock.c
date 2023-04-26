/* 
 * File:   combination_lock.c
 * Author: xiaogan zhang 
 * 1596973
 *
 * Created on October 1, 2021, 9:39 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000

#define sequence_num 4
/* set the number of presses required */


void buzz_low(void){
    for(int i=0; i<75; i++){
        DDRA |= (1<<0);
        PORTA |= (1<<0);
        _delay_ms(2);
        PORTA &= ~(1<<0);
        _delay_ms(2);
    }
}
/* make a tone 250Hz with the buzzer of a frequency for 0.3sec, 
buzzer connected to PA0 */

void buzz_high(void){
    for(int i=0; i<150; i++){
        DDRA |= (1<<0);
        PORTA |= (1<<0);
        _delay_ms(1);
        PORTA &= ~(1<<0);
        _delay_ms(1);
    }
}
/* make a tone 500Hz with the buzzer of a frequency for 0.3sec */

void LEDon(void){
    DDRA |= (1<<1);
    PORTA |= (1<<1);
}
/* turn logic high on PA1, which connects to LED */

void LEDoff(void){
    DDRA |= (1<<1);
    PORTA &= ~(1<<1);
}
/* turn logic low on PA1, turning off LED */

uint8_t button1 (void){
    return !(PINB & (1<<0));
}
/* returns 1 if button 1 is pressed, connected to PB0 */

uint8_t button2 (void){
    return !(PINB & (1<<1));
}
/* returns 1 if button 2 is pressed, connected to PB1 */

uint8_t button3 (void){
    return !(PINB & (1<<2));
}
/* returns 1 if button 3 is pressed, connected to PB2 */

typedef enum {reset, ready_for_press, check_entry, correct_combo} state_t;
/* define a new state_t type, contains the state of the state machine */


int main(int argc, char** argv) {
    state_t state = reset;
    uint8_t counter = 0;
    uint8_t entry = 0;
    /* initializing data variables to be used in the state machine */
    
    uint8_t combo[sequence_num] = {1,2,3,1};
    /* set the correct combinations in an array */
    
    while(1){
        switch(state){
            case reset:
                DDRB &= 0;
                PORTB |= ((1<<0)|(1<<1)|(1<<2));
                /* using PB0,1,2 as input for buttons 1,2,3, enabling pull-up */
                
                DDRA |= ((1<<0)|(1<<1));
                PORTA &= 0;
                /* using PA0,1 as outputs to buzzer and LED */
                
                counter = 0;
                entry = 0;
                /* reset variables */
                
                state = ready_for_press;
                break;
          
            case ready_for_press:
                if(counter == sequence_num){
                    buzz_low();
                    buzz_high();
                    LEDon();
                    state = correct_combo;
                }
                else{
                    if(button1() || button2() || button3()){
                        if(button1()){
                            entry = 1;
                        }
                        else if(button2()){
                            entry = 2;
                        }
                        else if(button3()){
                            entry = 3;
                        }
          
                        buzz_low();
                        state = check_entry;
                    }
                }
                break;
                /* if the correct combination has been entered, play the correct buzzer sounds and turn 
                LED on, then state changes to correct_combo; if correct combination is not yet entered,
                detect any button presses and save it in the variable entry for comparison with the 
                correct sequence */
                
            case check_entry:
                if(entry == combo[counter]){
                    ++counter;
                    state = ready_for_press;
                }
                else{
                    buzz_high();
                    buzz_low();
                    state = reset;
                }
                break;
                /* if the entry is correct, increment counter; otherwise, play 
                the incorrect buzzer sounds and reset to the beginning */
            
            case correct_combo:
                if(button1() || button2() || button3()){
                    LEDoff();
                    buzz_low();
                    state = reset;
                }
                break;
                /* if any key is pressed, turn LED off and reset every back to the beginning */
            
        } 
    }
    
return (0);
}
