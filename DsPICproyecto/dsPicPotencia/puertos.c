/* 
 * File:   puertos.c
 * Author: Ricardo
 *
 * Created on 14 de febrero de 2017, 06:07 PM
 */
#include "system.h"
#include "puertos.h"

void puertos_config(void)
{
    // configurar tris de los peurtos digitales que se van  autilizar
    TRISB=0x0001; // configurado como salidas
}
