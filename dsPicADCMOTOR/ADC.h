/* 
 * File:   ADC.h
 * Author: Ricardo
 *
 * Created on 20 de febrero de 2017, 06:06 PM
 */

#ifndef ADC_H
#define	ADC_H

#include "system.h"

void ADC_config(void);
void ADC_ON(unsigned int prender);
void ADC_channel(unsigned char channel);
void ADC_pinconfig(void);
unsigned int ADC_samp(void);


#endif	/* ADC_H */

