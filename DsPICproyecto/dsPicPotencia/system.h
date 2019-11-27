/* 
 * File:   system.h
 * Author: Ricardo
 *
 * Created on 1 de febrero de 2017, 06:40 PM
 */
#include "p30F4013.h"
#ifndef SYSTEM_H
#define	SYSTEM_H

#define     FOSC    120000000

void osc_config(unsigned int parametro);
void osctun_config(void);
void FOSCc_config(void);
#endif	/* SYSTEM_H */

