/*
 * File:   timer0.c
 * Author: sn1011701
 *
 * Created on 31 de Maio de 2019, 15:42
 */

#include <xc.h>
#include <pic16f887.h>
#include "config.h"
#include "timer0.h"

int t0final = 0;
int t0cont = 0;

void intt0_1ms( void )
{
    if( ++t0cont >= t0final )
    {
        t0cont = 0;
    }
}

void setT0( int c )
{
    t0cont = c;
}
int statusT0( void )
{
    return( t0cont );
}



void setT0limite( int c )
{
    t0final = c;
}
int statusT0limite( void )
{
    return( t0final );
}

void initTimer0( void )
{
    INTCONbits.GIE = 0;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 0;

    TMR0 = 256 - 250;

    setT0limite( 1000 );
    
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
}

char T1, T2, T3, T4, T5, T6, T7, T8, T9;

void T0_1s(void)
{
    setT0limite(10000);
    if( statusT0() >= ( statusT0limite()/2 ) )
    {    
        T1 = 1;
    }
    else
    {    
        T1 = 0;
    }
}

int statusT0_1s (void)
{
    return (T1);
}
//
//void T0_2s(void)
//{
//    setT0limite(4000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T2 = 1;
//    }
//    else
//    {    
//        T2 = 0;
//    }
//}
//
//int statusT0_2s (void)
//{
//    return (T2);
//}
//void T0_3s(void)
//{
//    setT0limite(6000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T3 = 1;
//    }
//    else
//    {    
//        T3 = 0;
//    }
//}
//
//int statusT0_3s (void)
//{
//    return (T3);
//}
//void T0_4s(void)
//{
//    setT0limite(8000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T4 = 1;
//    }
//    else
//    {    
//        T4 = 0;
//    }
//}
//
//int statusT0_4s (void)
//{
//    return (T4);
//}
//void T0_5s(void)
//{
//    setT0limite(10000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T5 = 1;
//    }
//    else
//    {    
//        T5 = 0;
//    }
//}
//
//int statusT0_5s (void)
//{
//    return (T5);
//}
//void T0_6s(void)
//{
//    setT0limite(12000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T6 = 1;
//    }
//    else
//    {    
//        T6 = 0;
//    }
//}
//
//int statusT0_6s (void)
//{
//    return (T6);
//}
//void T0_7s(void)
//{
//    setT0limite(14000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T7 = 1;
//    }
//    else
//    {    
//        T7 = 0;
//    }
//}
//
//int statusT0_7s (void)
//{
//    return (T7);
//}
//void T0_8s(void)
//{
//    setT0limite(16000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T8 = 1;
//    }
//    else
//    {    
//        T8 = 0;
//    }
//}
//
//int statusT0_8s (void)
//{
//    return (T8);
//}
//void T0_9s(void)
//{
//    setT0limite(18000);
//    if( statusT0() >= ( statusT0limite()/2 ) )
//    {    
//        T9 = 1;
//    }
//    else
//    {    
//        T9 = 0;
//    }
//}
//
//int statusT0_9s (void)
//{
//    return (T9);
//}