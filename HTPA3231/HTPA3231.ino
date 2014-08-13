#include "SPI.h"

#define DATAOUT 11     //MOSI
#define DATAIN 12      //MISO
#define SPICLOCK 13    //sck
#define SLAVESELECT 10 //ss
#define MCLK 8
#define VD 9 


void setup()
{
  Serial.begin(9600);

  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  pinMode(MCLK,OUTPUT);
  pinMode(VD,INPUT);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);

  int addr = 100;
  delayMicroseconds(10000);
  digitalWrite(SLAVESELECT,LOW);
  delayMicroseconds(180);

  SPI.transfer(0x00);  
  SPI.transfer(addr);//read EEPROM command
  
}

char spi_transfer(volatile char data)
{
  SPDR = data;                    
  while (!(SPSR & (1<<SPIF)))
  {
  };
  return SPDR;                
}

int validDataCounter = 0;
bool isReadPixels = false;

void loop()
{   
  if( isReadPixels == false )
  {
    if( digitalRead(VD) == LOW )
    {
      validDataCounter = 0;
      SPI.transfer(0x00);
      SPI.transfer(0x00);
    }     
  }

}

