/* 
 * File:   MASTER.c
 * Author: Daniela Baldizon
 *
 * Created on 12 de febrero de 2020, 02:16 PM
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
#include "RXTX.h"
#include "SPIM.h"
#define _XTAL_FREQ 4000000


void main(void){
    //CONFIGURACION DE PUERTOS
    ANSELH = 0;
    ANSEL = 0;
    TRISB = 0;
    PORTB = 0;
    TRISA = 0;
    PORTA = 0;
    //CONFIG 
    UART_Init(9600);
    unsigned char POT1; //VARIABLES QUE SE LEEN DEL ADC
    unsigned char POT2;
    uint8_t COMPU = 0;
    
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    while(1){
        UART_Write(POT1); //ESCRIBIR EL ADC A LA COMPU
        UART_Write(POT2);
        
        COMPU = UART_Read();//LEER LO QUE SE LE MANDA DE LA COMPU
      //  PORTB = COMPU; //ESCRIBE EN EL PUERTO B LO QUE RECIBE DE LA COMPU
      //  __delay_ms(5);
        
        spiWrite(0x01);             //ENVIA UN 1 PARA PEDIR EL VALOR DE POT1
        POT1 = spiRead();           //GUARDA EL VALOR
        PORTB = POT1;
        __delay_ms(0.1);
        
        
        spiWrite(0x02);         //ENVIA COMANDO PARA EL VALOR POT2
        POT2 = spiRead();      //GUARDA EL VALOR
        PORTA = POT2;
        __delay_ms(0.1);  
        
    }//CIERRE DEL WHILE  
}//CIERRE DEL MAIN