
#include <xc.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "leitorLM35_v07.h"
#include <stdio.h>
#include "recept.h"


volatile  LCDbits_t LCD __at(0x008);  

void initLCD( void )
    {
        LCD.B0  = 0;
        LCD.B1  = 0;
        LCD.RS  = 0;
        LCD.BUS = 0x3;
        LCD.EN  = 1;
        TRISD = 0xC0;
        
        delay(10);
        
        cmdLCD(LCD_DATA_BITS_4);
        cmdLCD(LCD_LINE2);
        cmdLCD(LCD_ON);
        cmdLCD(LCD_CLEAR);
        cmdLCD(LCD_HOME);
        
        delay(10);
    }

void cmdLCD( unsigned char cmd )
{
        volatile REGnibble_t nibble;
   
        nibble.HILO = cmd;
        LCD.RS = 0;
        LCD.BUS = nibble.HI ;
         LCD.EN = 0;
        if( cmd == LCD_CLEAR || cmd == LCD_HOME )   
        delay(2);
        else 
        delay(2);    
        LCD.EN = 1;
   
        if( cmd != (LCD_DATA_BITS_4) )
    {
       LCD.RS = 0;
       LCD.BUS = nibble.LO;
       LCD.EN = 0;
       if( cmd == LCD_CLEAR || cmd == LCD_HOME )
            delay(2);
       else
            __delay_us(40);    
       LCD.EN = 1;
    }
}

void putLCD( unsigned char c )
 {
        volatile REGnibble_t nibble;
   
        nibble.HILO = c;
        LCD.RS = 1;
        LCD.BUS= nibble.HI;
        LCD.EN = 0;
        delay(2);
        LCD.EN = 1;

        LCD.RS = 1;
        LCD.BUS = nibble.LO;
        LCD.EN = 0;
        delay(2);
        LCD.EN = 1;
}
void gotoxy( unsigned char x, unsigned char y )
{
        cmdLCD((LCD_GOTOL0 | LCD_GOTOL1 * y) + (x & 0X3F));    
}
void writeLCD( unsigned char x, unsigned char y, const char * ptr )
{
        gotoxy(x,y);
        while( *ptr )
        putLCD( *ptr++ );    
}

char lcdb0(void)
{
    return(LCD.B0);
}
char lcdb1(void)
{
    return(LCD.B1);
}

void SplashScreen0(void)
{
    writeLCD(4,0, "ELECTRIC");  
    writeLCD(4,1, "PULL UP");
}
void SplashScreen1(void)
{
    writeLCD(4,0, "Aquisitor");
    writeLCD(4,1, "de Dados"); 
}

void Menu(void)
{
    writeLCD(0,0, "SELETOR DE TELAS");
    writeLCD(3,1, "[A] [B] [C]"); 
    
}

void Telaprincipal(void)
{

    writeLCD(0,0, "Temp. Atual:   C");
    gotoxy(14,0);putLCD(0xDF);
    
    
}
void tempatt (void)
{
    int temp = temperaturaLer() ;
    char Tp[] = {"00"};
    Tp[0] =(temp/10)+0x30;   //Encontra a dezena da temperatura programada e converte em ASCII 
    Tp[1] =(temp%10)+0x30;  //Encontra a unidade da temperatura programada e converte em ASCII 
    writeLCD(12,0,Tp); 
}
void TempMed(void)
{   
    unsigned char Media;
    char md[] = {"00"};
    writeLCD(0,0, "Temp. Med.:    C");
    gotoxy(14,0);putLCD(0xDF);  
    Media = media();
    md[0] =(Media/10)+0x30;   //Encontra a dezena da temperatura programada e converte em ASCII 
    md[1] =(Media%10)+0x30;  //Encontra a unidade da temperatura programada e converte em ASCII 
    writeLCD(12,0,md); 

}

void showtemp (void)
{
    writeLCD(0,0, "Saving...");
//    writeLCD(0,1, "Limiar Min.:   %"); 
//    writeLCD(0,12, "salvatemp()"); 
    
}
