
#define _XTAL_FREQ 20000000 // necessary for __delay_us
#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF
#pragma intrinsic(_delay)

#include <xc.h>
#include <stdio.h>
#include <proc/pic16f886.h>

int estado;

void init_timer2() {

    T2CONbits.TMR2ON = 1;
    T2CONbits.TOUTPS = 0;
    T2CONbits.T2CKPS = 0;
    PIE1bits.TMR2IE = 1;
    PIR1bits.TMR2IF = 0;

    PR2 = 166;
}

void __interrupt() TMR2_int(void) {
    if (PIR1bits.TMR2IF) {
        
        
        CCPR2L = estado;

        PIR1bits.TMR2IF = 0;
    }
}

void initPWM(void) {

    CCP2CONbits.DC2B0 = 0;
    CCP2CONbits.DC2B1 = 0;
    CCP2CONbits.CCP2M = 0b1100;
    CCPR2L = 0;
}

void cambioPotencia(int potencia) {

    estado = (potencia / 100)*166;
}

void main(void) {

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    OSCCON = 0b00001000; // External cristal
    TRISC = 0;

    init_timer2();
    initPWM();

    cambioPotencia(100);

    while (1);
}
