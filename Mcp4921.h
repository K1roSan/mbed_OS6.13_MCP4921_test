#ifndef MCP4921_H
#define MCP4921_H

#include "mbed.h"

/**
* The MCP4921 is a single 12 bit DAC.
 The maximum voltage output is limited by the input voltage at V_DD which can go up to about 5.5V.

* Datasheet: http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en020398
*
*Exemple:
@code
//Mbed            Mcp4921
//p11: Mosi <---> p4:Sdi
//p12: Miso No Connected
//p13: Sck  <---> p3:Sck
//p14       <---> p2:Cs
//Vout      <---> p1:Vdd
//Vout      <---> p6: Vref
//Gnd       <---> p7:Gnd
//Gnd       <---> p5:Ldac

#include "mbed.h"
#include "Mcp4921.h"

Mcp4921 cna(p11,p13,p14,500000);
int main()
{
 static int mv;    
    while(1) {
       cna.write_mV(mv);
        
        mv+=500;
        if(mv>4000)
        mv=0;   
    }
}

@endcode
*/

class Mcp4921
{

public:
    /**Initializes the MCP 4921 DAC with the frequency
    
    */
    Mcp4921(PinName _mosi,PinName _sck,PinName _cs);

    /** @returns The frequency use by the Mcp4921
       */
    //int getFrequency(void);
    void setFrequency(int _frequency);

    /** Writes a value between 0-4095 to the currently selected DAC output
    * @param dataIntNum A value from 0-4095 to write to the DAC register
    */
    void write(int dataIntNum);

    /** Writes a float value between 0.0-1.0 to the currently selected DAC output
       * @param dataFloat A value from 0.0-1.0 to write to the DAC register
       */
    void write(float dataFloat);
    
     /** Writes a value in mV to the DAC outputs.
    * The output will only be accurate if Vref is set to the appropriate voltage reference scaling factor. 
    * @param millivolt The desired voltage output in millivolts
    */
    void write_mV(int millivolt);

    /**An operator for shorthand write(int)
    */
    void operator=(int dataIntNum);


    /**An operator for shorthand write(float)
    */
    void operator=(float dataFloat);


protected:
//
    void setup(void);
    SPI mySPI;
    DigitalOut myCs;
    int myFrequency;

};

#endif