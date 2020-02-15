/* 
 * File:   slave.c
 * Author: Daniela Baldizon
 *
 * Created on 12 de febrero de 2020, 08:18 PM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "SPIS.h"
#include "ADC.h"
#define _XTAL_FREQ 4000000

uint8_t adc1;
uint8_t adc2;
uint8_t canal = 0;
char opcion;

void __interrupt() ISR(void){
    if(PIR1bits.ADIF == 1){ // SI SE HABILITA LA INTERRUPCION
        if(canal == 0){
            ADCON0bits.CHS = 10;    //CANAL 10
            adc1 = ADRESH; // guarda en la variable el valor del adres
            canal = 1; //CAMBIA LA VARIABLE PARA QUE HAGA EL OTRO ADC
            ADIF = 0; //LIMPIAR LA BANDERA
        }
        else if(canal == 1){
            ADCON0bits.CHS = 12;    //CANAL 12
            adc2 = ADRESH; //PASA EL VALOR DEL ADC
            canal = 0; //CAMBIA LA VARIABLE PARA QUE HAGA EL OTRO ADC
            ADIF = 0;//LIMPIAR BANDERA
        }
        ADCON0bits.GO = 1;      //INICIA EL ADC
    }
    
    if(SSPIF==1){ // SI LA BANDERA DEL SPI ESTÁ ARRIBA
        opcion = spiRead(); // RECIBE LA ORDEN Y LA REVISA
        if(opcion == 1){
            spiWrite(adc1); //MANDA EL VALOR 1
        }
        else if(opcion == 2){
            spiWrite(adc2); //MANDA EL VALOR 2
        }
        SSPIF = 0; //LIMPIAR LA BANDERA DEL SPI 
    }
    
}

void main(void){
    //CONFIG
    ANSELH = 0;
    ANSEL = 0;
    TRISD = 0;
   
    TRISA = 0;
    PORTA = 0;
    
    //ADC
    ADC_CONFIG(12,0); //CANAL 12 JUSTIFIACION A LA IZQUIERDA
    ADC_CONFIG(10,0); //CANAL 10 JUSTIFICACION A LA IZQUIERDA
    ADC_INTERRUPT(); //INTERRUPCION DEL ADC
    ADCON0bits.GO = 1;      //INICIA EL ADC
    
    // SPI
    SSPIF = 0;
    SSPIE = 1;
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    while(1){
        //PORTA = adc1;
      //  ADCON0bits.GO = 1;      //INICIA EL ADC
       
    }
    
}