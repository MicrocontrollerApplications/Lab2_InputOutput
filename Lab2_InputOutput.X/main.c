/*
 * File:   newmain.c
 * Author: Sebastian Moosbauer
 *
 * Created on March 19, 2025, 11:24 AM
 */


#include <xc.h>

/**
 * Initialization function for our program. You'll learn to extend this today :)
 */
void __init(void);

void main(void) {
    // initialize microcontroller
    __init();
    
    unsigned char button;
    
    while(1){
        button = PORTBbits.RB2; // Read button TL
        
        if (button == 0) { // TL pressed?
            LATBbits.LATB3 = 0; // LED2 on
        } else{
            LATBbits.LATB3 = 1;  // LED2 off
        }
        
        if (PORTBbits.RB4 == 0) { // TR pressed?
            while (PORTBbits.RB4 == 0) { // wait until TR is not pressed anymore
                Nop();
            }
            
            LATBbits.LATB5 = !LATBbits.LATB5; //toggle LED4
        }
        Nop(); // Do nothing, a breakpoint may be placed here.
    }
    
    return 0;
}

void __init(void){
    OSCCON = 0x50; // 500kHz internal clock (we'll learn that soon!))
    ANSELB = 0; // set all pins in register B to be digital
    TRISB = 0b00001010; //Input: RB2 and RB4; Output: all others
    LATB = 0b00001010; // Turn LEDs off
}
