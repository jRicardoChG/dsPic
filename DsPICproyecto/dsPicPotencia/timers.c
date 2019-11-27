/* 
 * File:   timers.c
 * Author: Ricardo
 *
 * Created on 17 de febrero de 2017, 02:38 PM
 */
#include "timers.h"
#include "p30F4013.h"

void timer1_config(unsigned int PR1setup)
{
    //timer tipo A
    //ecuacion T=(4/fosc)*prescaler*(PR1+1) seasyume fosc =7.5Mhz*16 t=33ns 30 MIPS EXITE DUDA REVISAR CON OSCILOSCOPIO
    //las caracteristicas de TxCON se encuentran en el archivo dsPIC reference manual (DS70046) recomendado por el datasheet
    // configuraré esta vez para que se limpie cada 1ms
    IFS0bits.T1IF=0; // limpio la bandera
    T1CONbits.TON=0; // timer apagado
    T1CONbits.TSIDL=0; // se apaga en estadi idle
    T1CONbits.TGATE=0; //acumulador del gate desactivado
    T1CONbits.TCKPS=0; // preescala 8
    T1CONbits.TSYNC=0; // no sincronizado con una fuente externa
    T1CONbits.TCS=0; // fuente de reloj (FOSC/4)
    PR1=PR1setup; //configuro el periodo de conteo para 500ms 58593
}
void timer1_on_off(unsigned char pulso)
{
    T1CONbits.TON=pulso;
}
unsigned char timer1_test(void)
{
    if(IFS0bits.T1IF==1)
    {
       IFS0bits.T1IF=0;
        return 1;
    }
    else
    {
        return 0;
    }
}
void timer2_config(unsigned int PR2setup)
{
    //timer tipo B solo tiene un bit t32 par unirlo a otro timer tipo C
    //ecuacion T=(4/fosc)*prescaler*(PR1+1) seasyume fosc =7.5Mhz*16 t=33ns 30 MIPS 
    //las caracteristicas de TxCON se encuentran en el archivo dsPIC reference manual (DS70046) recomendado por el datasheet
    // configuraré esta vez para que se limpie cada 1ms
    IFS0bits.T2IF=0; // limpio la bandera
    T2CONbits.TON=0; // timer apagado
    T2CONbits.TSIDL=0; // se apaga en estadi idle
    T2CONbits.TGATE=0; //acumulador del gate desactivado
    T2CONbits.TCKPS=0; // preescala 8
    T2CONbits.TCS=0; // fuente de reloj (FOSC/4)
    T2CONbits.T32=0; // timer de 16 bits
    PR2=PR2setup; //configuro el periodo de conteo para 500ms 58593
    
}
void timer2_on_off(unsigned char pulso)
{
    T2CONbits.TON=pulso;
}
unsigned char timer2_test(void)
{
    if(IFS0bits.T2IF==1)
    {
       IFS0bits.T2IF=0;
        return 1;
    }
    else
    {
        return 0;
    }
}
void timer3_config(unsigned int PR3setup)
{
    //timer tipo C
    //ecuacion T=(4/fosc)*prescaler*(PR1+1) seasyume fosc =7.5Mhz*16 t=33ns 30 MIPS EXITE DUDA REVISAR CON OSCILOSCOPIO
    //las caracteristicas de TxCON se encuentran en el archivo dsPIC reference manual (DS70046) recomendado por el datasheet
    // configuraré esta vez para que se limpie cada 1ms
    IFS0bits.T3IF=0; // limpio la bandera
    T3CONbits.TON=0; // timer apagado
    T3CONbits.TSIDL=0; // se apaga en estadi idle
    T3CONbits.TGATE=0; //acumulador del gate desactivado
    T3CONbits.TCKPS=0; // preescala 8
    T3CONbits.TCS=0; // fuente de reloj (FOSC/4)
    PR3=PR3setup; //configuro el periodo de conteo para 500ms 58593
}
void timer3_on_off(unsigned char pulso)
{
    T3CONbits.TON=pulso;
}
unsigned char timer3_test(void)
{
    if(IFS0bits.T3IF==1)
    {
       IFS0bits.T3IF=0;
        return 1;
    }
    else
    {
        return 0;
    }
}
void timer45_config(long PR45setup)
{
    // configuracion de los timers 4/5 para un timer de 32bits
    // la configuracion se toma con los registros del timer 4 la bandera de t4con, y los enable de interrupcion con t5ie t5if
    //timer tipo B solo tiene un bit t32 par unirlo a otro timer tipo C
    //ecuacion T=(4/fosc)*prescaler*(PR1+1) seasyume fosc =7.5Mhz*16 t=33ns 30 MIPS 
    //las caracteristicas de TxCON se encuentran en el archivo dsPIC reference manual (DS70046) recomendado por el datasheet
    // configuraré esta vez para que se limpie cada 1ms
    IFS1bits.T5IF=0; // limpio la bandera
    T4CONbits.TON=0; // timer apagado
    T4CONbits.TSIDL=0; // se apaga en estadi idle
    T4CONbits.TGATE=0; //acumulador del gate desactivado
    T4CONbits.TCKPS=3; // preescala 8
    T4CONbits.TCS=0; // fuente de reloj (FOSC/4)
    T4CONbits.T32=1; // timer de 32 bits
    PR4=PR45setup&0x0000ffff;
    PR5=(PR45setup&0xffff0000)>>16; // combinacion de pr4 y pr5 para el timer de 32 bits
}   
void timer45_on_off(unsigned char pulso)
{
    T4CONbits.TON=pulso;
}
unsigned char timer45_test(void)
{
    if(IFS1bits.T5IF==1)
    {
       IFS1bits.T5IF=0;
        return 1;
    }
    else
    {
        return 0;
    }
}