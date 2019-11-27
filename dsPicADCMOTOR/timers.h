/* 
 * File:   timers.h
 * Author: Ricardo
 *
 * Created on 1 de febrero de 2017, 06:40 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

void timer1_config(unsigned int PR1setup);
void timer1_on_off(unsigned char pulso);
unsigned char timer1_test(void);
void timer2_config(unsigned int PR2setup);
void timer2_on_off(unsigned char pulso);
unsigned char timer2_test(void);
void timer3_config(unsigned int PR3setup);
void timer3_on_off(unsigned char pulso);
unsigned char timer3_test(void);
void timer45_config(long PR45setup);
void timer45_on_off(unsigned char pulso);
unsigned char timer45_test(void);
#endif	/* TIMERS_H */

