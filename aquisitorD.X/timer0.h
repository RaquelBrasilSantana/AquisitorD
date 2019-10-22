/* 
 * File:   timer0.h
 * Author: sn1011701
 *
 * Created on 31 de Maio de 2019, 15:45
 */

#ifndef TIMER0_H
#define	TIMER0_H

void initTimer0();
void intt0_1ms( void );
void setT0( int c );
int statusT0( void );
void setT0limite( int c );
int statusT0limite( void );
int _statusT0_s (void);

void T0_1s(void);
int statusT0_1s (void);

//void T0_2s(void);
//int statusT0_2s (void);
//
//void T0_3s(void);
//int statusT0_3s (void);
//
//void T0_3s(void);
//int statusT0_3s (void);
//
//void T0_4s(void);
//int statusT0_4s (void);
//void T0_5s(void);
//
//int statusT0_5s (void);
//
//void T0_6s(void);
//int statusT0_6s (void);
//
//void T0_7s(void);
//int statusT0_7s (void);
//
//void T0_8s(void);
//int statusT0_8s (void);
//
//void T0_9s(void);
//int statusT0_9s (void);

#endif	/* TIMER0_H */

