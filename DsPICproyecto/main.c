/* 
 * File:   main.c
 * Author: Ricardo
 *
 * Created on 1 de febrero de 2017, 06:41 PM
 */
#include "p30F4013.h"
#include "system.h"
#include "puertos.h"
#include "timers.h"
#include "UART.h"
#include "ADC.h"

// DSPIC30F4013 Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FOSFPR = FRC_PLL16       // Oscillator (FRC w/PLL 16x)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_OFF         // PBOR Enable (Disabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define     ENABLE   1
#define     DISABLE  0
#define     ISR      __attribute__((interrupt, auto_psv))

//variables globales para las interrupciones
int usuario=0,contt2=0;
int flagt2=0,valor=2000;

void ISR _U1RXInterrupt(void)
{
        usuario=urx();
        if(usuario=='s')
        {
            LATBbits.LATB3=~LATBbits.LATB3;
            LATBbits.LATB2=~LATBbits.LATB2;
        }
        IFS0bits.U1RXIF=0;
}
void ISR _T2Interrupt(void)
{
    IFS0bits.T2IF=0;
    contt2=contt2+62;
    if(contt2>=valor)
    {
        LATBbits.LATB4=0;
    }
    if(contt2>=4000)
    {
        contt2=0;
        LATBbits.LATB4=1;
    }
}
void Separador(unsigned int vector[], unsigned int valorlectura)
{
    unsigned int temp=0,cont=0,cont2=0,cont3=0,cont4=0;
    temp=valorlectura;
    if (temp>999)
    {
        while(temp>999)
        {
            cont++;
            temp=temp-1000;
            vector[0]=cont;
        }
    }
    else
    {
        vector[0]=0;
    }
    if(temp>99)
    {
       while(temp>99)
        {
            cont2++;
            temp=temp-100;
            vector[1]=cont2;
        } 
    }
    else
    {
        vector[1]=0;
    }
    if(temp>9)
    {
       while(temp>9)
        {
            cont3++;
            temp=temp-10;
            vector[2]=cont3;
        } 
    }
    else
    {
        vector[2]=0;
    }
    if(temp>0)
    {
       while(temp>0)
        {
            cont4++;
            temp=temp-1;
            vector[3]=cont4;
        } 
    }
    else
    {
        vector[3]=0;
    }
}

void main(void)
{
    // inicializacion de variables
    unsigned int vectorlectura[5];
    unsigned int cont=0;//valor=0;
    // configuracion de perifericos
    puertos_config();
    osc_config(0x1180);
    osctun_config();
    timer1_config(3749); // timer configurado a 2 ms
    timer1_on_off(ENABLE);
    timer2_config(29); // timer configurado para 1 us
    UART_config(460800);
    ADC_config();
    ADC_pinconfig();
    ADC_channel(0);
    ADC_ON(ENABLE);
    //habilitando interrupciones
    INTCON1bits.NSTDIS=1; //no pueden haber interrupciones dentro de las interrupciones
    IEC0bits.U1RXIE=1;  // interrupcion por recepcion en rx de la uart1
    IPC2bits.U1RXIP=2;  // prioridad de la interrupcion
    IFS0bits.U1RXIF=0;
    IEC0bits.T2IE=1;    // Interrupcion por timer2
    IPC1bits.T2IP=7;    // prioridad de la interrupcion
    IFS0bits.T2IF=0;    //
    // programa principal
    timer2_on_off(ENABLE);
    LATBbits.LATB4=1;
    LATBbits.LATB2=1;
    LATBbits.LATB3=0;
    
    while(1)
    {
        if(timer1_test()==1)
        //if(flagt1==1)
        {
            cont++;
                    if(cont==5)
                    {
                        IEC0bits.U1RXIE=0;
                        IEC0bits.T2IE=0;
                        valor=ADC_samp();
                        IEC0bits.T2IE=1;
                        IEC0bits.U1RXIE=1;
//                        Separador(vectorlectura,valor);
//                        utx(vectorlectura[0]+48);
//                        utx(vectorlectura[1]+48);
//                        utx(vectorlectura[2]+48);
//                        utx(vectorlectura[3]+48);
//                        utx(13);
//                        utx(10);
                        cont=0;
                        LATBbits.LATB1=~LATBbits.LATB1;
                    }
        }
    }
}

