/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Mcp4921.h"

// Maximum number of element the application buffer can contain
#define MAXIMUM_BUFFER_SIZE                                                  32
// Create a BufferedSerial object with a default baud rate.
static BufferedSerial serial_port(USBTX, USBRX);

#define DAC_FREQUENCY     500000
// Blinking rate in milliseconds
#define DAC_BLINKING_RATE     10us

Mcp4921 myDAC1(PB_5, PB_3, PF_1);//mosi sck cs 

int main()
{
    // Initialise the digital pin LED1 as an output
    //DigitalOut led(LED1);//do not use LED1(=PB_3)
    // Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(8, BufferedSerial::None, 1); //8bit

    // Application buffer to receive the data
    char buf[MAXIMUM_BUFFER_SIZE] = {0};
    int i,num;


    myDAC1.setFrequency(DAC_FREQUENCY);

    while (true) {

        //led = !led;

        for(i=0;i<4096;++i){
            num = sprintf(buf, "data:%d \n",i);
            serial_port.write(buf, num);

            myDAC1.write(i);
            //ThisThread::sleep_for(DAC_BLINKING_RATE);
            
        }

        //led = !led;

        for(i=4905;i>=0;--i){
            num = sprintf(buf, "data:%d \n",i);
            serial_port.write(buf, num);

            myDAC1.write(i);
            //ThisThread::sleep_for(DAC_BLINKING_RATE);
        }
    }
    
}
