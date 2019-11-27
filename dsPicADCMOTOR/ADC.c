/* 
 * File:   ADC.c
 * Author: Ricardo
 *
 * Created on 20 de febrero de 2017, 06:05 PM
 */
#include "ADC.h"

void ADC_config(void)
{
    ADCON1bits.ASAM=0;      // el usuario elige el momento del muestreo
    ADCON1bits.SSRC=7;      // el contador interno terminar el muestreo y empieza la conversion
    ADCON1bits.FORM=00;     // formato de entrega del dato del covnersor= entero 12 bits
    ADCON1bits.ADSIDL=0;    // el adc sigue funcionando en estado idle
    ADCON1bits.ADON=0;      // ADC esta apagado
    ADCON2bits.ALTS=0;      // el mux A tiene siempre el dato de muestreo
    ADCON2bits.BUFM=0;      // divide el buffer en dos grupos de 8 palabras (16 bits))
    ADCON2bits.SMPI=0000;   // se toma una sola muestroy se manda al conversor, sucede interrupcion
    ADCON2bits.CSCNA=0;     // escanea las entradas adjuntas al mux a cuando se desea un muestreo secuencial
    ADCON2bits.VCFG=000;    // referencias de voltaje por los pines AVdd AVss
    ADCON3bits.ADCS=39;     // aplicacion de la ecuacion ADCS=2TAD/TCY -1 TAD=667ns, ver datasheet TCY=4/FOSC
    ADCON3bits.ADRC=0;      // A/D internal RC clock para estado idle
    ADCON3bits.SAMC=00001;  // numero de clock de adquisicion
}
void ADC_ON(unsigned int prender)
{
    ADCON1bits.ADON=prender;
}
void ADC_channel(unsigned char channel)
{   
    ADCHS=channel;          // elijo el pin que se conecta al channel 0
}
void ADC_pinconfig(void)
{
    TRISB=0x0001;           // configurado como entrada=1
    ADPCFG=0xFFFE;          // 0 como analogico 1 cono digital
    ADCSSL=0x0000;          // 1 se elige como entrada de MUX A, 0 se salta
}
unsigned int ADC_samp(void)
{
    ADCON1bits.SAMP=1;
    while(!ADCON1bits.DONE){};
    return ADCBUF0;
}
