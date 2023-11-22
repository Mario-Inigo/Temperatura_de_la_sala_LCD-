/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Grove_LCD_RGB_Backlight.h"

#define WAIT_TIME_MS 500 
AnalogIn sensor(A1);
Grove_LCD_RGB_Backlight rgbLCD(PB_9,PB_8);

float temperaturaSalida;
float NTC;
float T0 = 298.15;
float Vout;
int beta = 4250;
int R0 = 100000;
char cadena[16];

int main()
{
    Vout = sensor*3.3;
    
    NTC = (R0/Vout)*5-R0;

    temperaturaSalida = (beta / (log(NTC/R0)+(beta/T0)))- 273.15;

    while (true)
    {
        rgbLCD.locate(0,0);
        rgbLCD.setRGB(0xff, 0xff, 0xff);                //set the color 
        sprintf(cadena,"Temperatura %f\n",temperaturaSalida);
        rgbLCD.print(cadena);

        thread_sleep_for(WAIT_TIME_MS);
    }
}
