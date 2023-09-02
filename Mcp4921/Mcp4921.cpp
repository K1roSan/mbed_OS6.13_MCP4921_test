#include "Mcp4921.h"

Mcp4921::Mcp4921(PinName _mosi,PinName _sck,PinName _cs):mySPI(_mosi,NC,_sck),myCs(_cs)
{
    //myFrequency=_frequency;
    setup();
}
//---------------------------------------
void Mcp4921::setFrequency(int _frequency)
{
    mySPI.frequency(_frequency);
}

//int Mcp4921::getFrequency(void)
//{
//    return myFrequency;
//}
//--------------------------------------
void Mcp4921::write(int dataIntNum)
{
 //valid input values are 0 - 4095.   4096 should scale to Vref.  

    if(dataIntNum >4095)
        dataIntNum=4095;

    if(dataIntNum <0)
        dataIntNum=0;

    int16_t temp=0;
    temp=dataIntNum | 0x7000;

    myCs=0;
    wait_us(1);
    mySPI.write(temp);

    myCs=1;
    wait_us(1);
}
//--------------------------------------
void Mcp4921::write_mV(int millivolt){
    
    if(millivolt >3300)
        millivolt=3300;
        
    if(millivolt <0)
        millivolt=0;
        
  int val=(millivolt*4095)/3300;
  
  write(val);      
}
//--------------------------------------
void Mcp4921::write(float dataFloat)
{
//valid input values are 0.0 - 1.0   with 1.0 should scale to Vref.   
    if(dataFloat >1.0)
        dataFloat=1.0;

    if(dataFloat <0)
        dataFloat=0;

    float temp=4095*dataFloat;

    write((int)temp);
}
//--------------------------------------
void Mcp4921::operator=(int dataIntNum)
{
    write(dataIntNum);
}
//--------------------------------------
void Mcp4921::operator=(float dataFloat)
{
    write(dataFloat);
}
//--------------------------------------
void Mcp4921::setup(void)
{
    myCs=1;
    //mySPI.frequency(myFrequency);  //
    mySPI.format(16,0);       //16 bits + mode 0
}
//