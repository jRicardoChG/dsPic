/* 
 * File:   system.c
 * Author: Ricardo
 *
 * Created on 14 de febrero de 2017, 03:38 PM
 */
#include "system.h"
void osc_config(unsigned int parametro)
{
    unsigned char parametroL=0,parametroH=0;
    parametroL=parametro&0x00FF;
    parametroH=(parametro&0xFF00)>>8;
    OSCCONL=0x46;
    OSCCONL=0x57;
    OSCCONL=parametroL;
    OSCCONH=0x76;
    OSCCONH=0x9A;
    OSCCONH=parametroH;
}
void osctun_config(void)
{
    OSCTUN=0x0000; // poner en 0 para frecuencia nominal 8Mhz o 7.37 o 7.5 Mhz, EXISTE DUDA REVISAR CON OSCILOSCOPIO
}


