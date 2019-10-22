
#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "lcd.h"
#include "recept.h"
#include "leitorLM35_v07.h"  
//#include<pic16f877.h>
#include "delay.h"
    
/***************************************************************************************************************
    Cria fun��es para database de dados de medicacao do sensor de temperatura.
    Contem 5 fun��es para usos.
    Primeira fun��o, que salva o valor de temperatura.
    Segunda fun��o, que reseta toda a memoria.
    Terceira fun��o, retorna a media das temperaturas.
    Quarta fun��o, retorna a moda das temperaturas.
    quinta fun��o, retorna as medianas
***************************************************************************************************************
    As temperaturas s�o salvas de formas quantitativas, ou seja, utilizando se da EEPROM do processador
    � realizado um incremetento na variavel, cada vez que sua temperatura � informada.
    Exemplo:
    A EEPROM da posi��o "20" representa a posi�ao de 20�C, cada vez que a fun��o "salvatemp(20)" � chamada
    a posi�ao 20 soma-se 1 no valor da memoria.
    Imaginemos que a "salvatemp(20)" foi chamada 30 vezes, ent�o a posi��o 20 da eeprom contem o valor 30. Se 
    chamarmos mais uma vez a "salvatemp(20)", a posi��o 20 da eeprom vai receber o valor 31.
 ***************************************************************************************************************
 */


    
    
void salvatemp(unsigned char temp)
{
    unsigned int valor;               //Variavel de controle
    valor = EEPROM_read(temp);         //Verifica quantas vezes essa temperatura j� foi solititada.
    valor++;                           //Adciona mais uma chamada ao valor.
    EEPROM_write(temp,valor);          //Salva novo valor de chamadas da temperatura.
}

/* Apaga todos os dados coletados */
void resetemp(void)
{
   for(char i=0; i<100; i++)
    {          //Repete em todas as 99 indica��es de temperatura.         
        EEPROM_write(i,0b0);             //Zera os dados medidos.
    }
}

/* A media aritimetica consiste na soma de todos os termos de uma fun��o pelo numero de termos que essa fun��o apresentou */
unsigned char media(void)
{             
    unsigned long divisao = 0;          //Variavel para salvar o numero de dados computados.
    unsigned long valor = 0;            //Variavel para armazenar todos os valores somados.
    for(char i=0; i<100; i++)
    {         //Repete em todas as 99 indica��es de temperatura.
        unsigned int ee = 0;          //Variavel para calculos.
        ee = EEPROM_read(i);           //Le valor de chamadas de temperatura na fun��o e armazena.
        valor += ee * i;               //Soma o valor da temperatura x repeti��es de chamada.
        divisao += ee;                 //Soma numero de chamadas.
    }
    unsigned char retorno =(valor/divisao); //Calcula media.
    return retorno;                         //Retorna Media.
}

/* A moda consiste em encontrar o numero que tem o maior numero de repeti��es dentro da sequencia */
unsigned char moda(void)
{
    unsigned int Mvalor = 0;    // cria valor de compara��o 1.
    unsigned int valor = 0;     // cria valor de compara��o 2.
    unsigned char temp = 0;     // cria variavel para retorno.
    for(char i=0; i<100; i++)
    {  // Verifica em todas as possibilidades de temperatura.
        valor = EEPROM_read(i);
        if(Mvalor<valor)
        {       // Caso essa temperatura apresentou mais repeti��es que a anterior, ela � armazenada.
            Mvalor = valor;     //Armazena nova temperatura.
            temp=i;             //Armazena Graus da temperatura
        }
    }
    return (temp);              //Devolve a temperatura da moda.
}

/*A mediana � o valor que se encontra na exata metade dos valores medidos*/
unsigned char mediana(void)
{
    unsigned long ee = 0;                             //cria valor de compara��o 2.
    unsigned long ee2 = 0;                            //cria valor de compara��o 2.
    for(char i=0; i<100; i++)
    {              //Verifica o numero de termos (temperaturas enviadas)
        ee +=EEPROM_read(i);                //salva na variavel ee.
    }
    for(unsigned char i=0; i<100; i++)
    {     // verifica onde se encontra o meio da media.
        ee2 +=EEPROM_read(i);               //salva para verificar a se o valor esta proximo ao meio.
            if(ee2 >= (ee/2))
            {              //Caso o temperatura esteja no meio da medi��o, 
               return i;                    //retorna o valor de temperaura
               break;
            }
    }
    return -1;
}

void EEPROM_write(unsigned char pont,unsigned int value)
{
    EEPROM_WriteByte(pont,value/256);
    EEPROM_WriteByte(pont+100,value%256);
}
int EEPROM_read(unsigned char pont)
{
       return ((EEPROM_ReadByte(pont)*256)+EEPROM_ReadByte(pont+100));
}

void EEPROM_WriteByte(unsigned char eepromAddress, unsigned char eepromData)
{
    unsigned char gie_Status;
    while(WR);            // check the WR bit to see if a previous Write operation is in progress
    EEADR=eepromAddress;  // Write the address to EEADR.
    EEDATA=eepromData;    // load the 8-bit data value to be written in the EEDATA register.
    EECON1bits.EEPGD = 0;
    WREN=1;               // Set the WREN bit to enable eeprom operation.
    gie_Status = GIE;     // Copy the current Interrupt state
    GIE = 0;              // Disable the interrupts
    EECON2=0x55;          // Execute the special instruction sequence
    EECON2=0xaa;          // Refer the datasheet for more info
    WR=1;                 // Set the WR bit to trigger the eeprom write operation.
    GIE = gie_Status;     // Restore the interrupts
    delay(1);
    WREN=0;               // Disable the EepromWrite
}
unsigned char EEPROM_ReadByte(unsigned char eepromAddress)
{
    while(RD || WR);           // check the WR&RD bit to see if a RD/WR is in progress
    EEADR=eepromAddress;       // Write the address to EEADR.
    EECON1bits.EEPGD = 0;
    RD = 1;                    // Set the RD bit to trigger the eeprom read operation.
    return(EEDATA);            // Return the data read form eeprom.
}
void tmron(void)
{
    TMR1IE=1;
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
    TMR1L = TMR1H = 0x00;
    T1CON  = 0b00110001;
}
