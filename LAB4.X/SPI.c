/* 
 * File:   SPI.c
 * Author: Daniela Baldizon
 *
 * Created on 12 de febrero de 2020, 02:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "SPI.h"
#include <pic16f887.h>

//CODIGO TOMADO DE ELECTROSOME https://electrosome.com/spi-pic-microcontroller-mplab-xc8/

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
  TRISC5 = 0;
  if(sType & 0b00000100) //If Slave Mode
  {
    SSPSTAT = sTransmitEdge;
    TRISC3 = 1;
  }
  else //If Master Mode
  {
    SSPSTAT = sDataSample | sTransmitEdge;
    TRISC3 = 0;
  }
  SSPCON = sType | sClockIdle;
}

static void spiReceiveWait()
{
  while ( !SSPSTATbits.BF ); // Wait for Data Receipt complete
}

void spiWrite(char dat) //Write data to SPI bus
{
  SSPBUF = dat;
}

unsigned spiDataReady() //Check whether the data is ready to read
{
  if(SSPSTATbits.BF)
    return 1;
  else
    return 0;
}

char spiRead()    // Read the received data
{
  spiReceiveWait();      // Wait until all bits receive
  return(SSPBUF); // Read the received data from the buffer
}

