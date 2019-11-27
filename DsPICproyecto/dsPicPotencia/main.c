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
unsigned long refe=80;
unsigned long cont=0;//valor=0;
unsigned int refeReal=0;

void ISR _U1RXInterrupt(void)
{
        usuario=urx();
        if(usuario=='+')
        {
            utx(usuario);
            refe++;
            if(refe>=179)
            {
                 refe=179;
            }
            else
            {
                if(refe<=1)
                {
                    refe=1;
                }
            }
        }
        if(usuario=='-')
        {
            refe--;
            utx(usuario);
            if(refe>=179)
            {
                refe=179;
            }
            else
            {
                if(refe<=1)
                {
                    refe=1;
                }
            }
        }
        IFS0bits.U1RXIF=0;
}
void ISR _INT0Interrupt(void)
{
    timer2_on_off(ENABLE);
    IFS0bits.INT0IF=0;
    refeReal=refe;
    LATBbits.LATB2=0;
}

void main(void)
{
    // inicializacion de variables
   // unsigned int vectorlectura[5];
    // configuracion de perifericos
    puertos_config();
    osc_config(0x1180);
    osctun_config();
    timer1_config(1379); // timer configurado a 1 us
    //timer1_on_off(ENABLE);
   timer2_config(1379); // timer configurado para 1 us
   timer3_config(1379);
   //timer2_on_off(ENABLE);
    UART_config(460800);

 //   habilitando interrupciones
    INTCON1bits.NSTDIS=1; //no pueden haber interrupciones dentro de las interrupciones
    IEC0bits.U1RXIE=1;  // interrupcion por recepcion en rx de la uart1
    IPC2bits.U1RXIP=2;  // prioridad de la interrupcion
    IFS0bits.U1RXIF=0;
    // interroucion por flanco ascendente en los pines externos
    INTCON2bits.INT0EP=0;
    IEC0bits.INT0IE=1;
    IPC0bits.INT0IP=2;
    IFS0bits.INT0IF=0;
  //   programa principal
    LATBbits.LATB2=0;
    while(1)
    {
        if(timer2_test()==1)
        {
            cont++;
            if(cont>=refeReal)
            {
                LATBbits.LATB2=1;
            }
            if(cont>=(refeReal+10))
            {
                cont=0;
                LATBbits.LATB2=0;
                timer2_on_off(DISABLE);
            }
        }
    }
}

