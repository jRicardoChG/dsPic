/* 
 * File:   UART.c
 * Author: Ricardo
 *
 * Created on 18 de febrero de 2017, 05:55 PM
 */
#include "UART.h"

void UART_config(unsigned long baudrate)
{
    unsigned int rate=0;
    U1MODEbits.STSEL=0;     // 1 bit de stop
    U1MODEbits.PDSEL=00;    // 8 bits data, no parity
    U1MODEbits.ABAUD=0;     // pin UxRX
    U1MODEbits.LPBACK=0;    // loopback off
    U1MODEbits.ALTIO=0;     // usar pines Rx y Tx
    U1MODEbits.USIDL=0;     
    U1MODEbits.UARTEN=1;    // habiltar transimison
    //////
    U1STAbits.OERR=0;       // bandera de buffer lleno apagada
    U1STAbits.ADDEN=0;      // no adress mode
    U1STAbits.URXISEL=00;   // se recibe un solo caracter, se prede bandera
    U1STAbits.UTXEN=1;      // UXTX se controla con la UART
    U1STAbits.UTXBRK=0;     // pon uxtx se maneja normal
    U1STAbits.UTXISEL=0;    // bandera de interrupcion se activa si hay como minimo 1 dato en el RSR 
    rate=(FOSC/(64*baudrate))-1;
    U1BRG=rate;
}

unsigned int urx(void)
{
    while(U1STAbits.URXDA==0){};
    return(U1RXREG);
}

void utx(unsigned int data)
{
    while(U1STAbits.UTXBF==1){};
        U1TXREG=data&0x00ff;
    while(U1STAbits.TRMT==0){};
}