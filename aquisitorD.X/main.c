#include <xc.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "teclado.h"
#include "leitorLM35_v07.h"
#include "timer0.h"
#include <stdio.h>
#include "recept.h"

#define LEDVED PORTCbits.RC0
#define LEDAMA PORTCbits.RC1
#define LEDVEM PORTCbits.RC2
char tim = 1;
int repeat = 0;
char var;
void __interrupt myISR(void);
   
void main(void) 
{
    initLCD();
    tecladoIniciar();
    temperaturaInicializar();
    resetemp();
    
    unsigned char nr;
 
    
    SplashScreen0();
    delay(100);
    cmdLCD(LCD_CLEAR);
    SplashScreen1();
    delay(100);
    
    tempatt();
    cmdLCD(LCD_CLEAR);
    TRISC=0x00;
    PORTC=0;
    
    tmron();
    Telaprincipal();
    
   while ( 1 )
    {
      
       nr = tecladoLer();
       
       if(nr != 0)
       {
           putLCD(nr);
       }
             
       switch (nr)
       {
           
           case 'A':        
                cmdLCD(LCD_CLEAR);
                Telaprincipal();   
                adcLer();
                temperaturaLer();
                tim = 1;
                break;
               
           case 'B':
                cmdLCD(LCD_CLEAR);
                showtemp ();
                salvatemp(temperaturaLer());       
                tim = 0;            
                break;
               
           case 'C':
                cmdLCD(LCD_CLEAR);
                TempMed();
                tim = 0;
                break;
               
           case 'D':             
                cmdLCD(LCD_CLEAR);
                Menu();
                tim = 0;                
                break;   

         }
       


     }
 }                
void __interrupt myISR(void)
{  
    if(TMR1IF)
    {
        repeat++;
        TMR1IF = 0;
        TMR1L = TMR1H = 0x00;       
        if(repeat >=2861)
        {
            salvatemp(temperaturaLer()); //Esse codigo acontece a cada 5 minutos.
            repeat = 0;
        }
    }
    if (tim == 1)
       {
           tempatt(); 
       }
}
