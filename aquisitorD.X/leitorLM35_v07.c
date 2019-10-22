#include <xc.h>
#include "config.h"
#include "delay.h"

void temperaturaInicializar(void)
{
    TRISA |= 0b00000001;                                                        // RA0 como entrada.
    ADIF = 0;									// Limpa Flag da interrupção do módulo.
    ADIE = 0;									// Desliga a interrupção do ADC.
    
#ifndef _PIC18									// Se for para 16F...
    ADCON0 = 0b10000001;                                                        // Configura  ADC com Fosc/32 e CH0.
    ADCON1 = 0b10000000;                                                        // Configura saída Justificada a direita e referência.
    ANSEL  = 0b00000001;                                                        // Seleciona pino RA0 como analógico. 
#elif   _PIC18									// Se for para 18F...
    ADCON2 = 0b10111010;							// Just Right, 20TAD, FOSC/32
    ADCON1 = 0b00001110;							// Seleciona Vref(0 e 5V) e AN0.
#endif
    delay(1);								// Aguarda...
}

unsigned int adcLer(void)
{
    unsigned int adc01Temp;							// Variável local temporária.
    delay(35);								// Atraso para iniciar ADC (Carga do capacitor de hold)
    
#ifndef _PIC18									// Se for para 16F...          
    ADCON0bits.ADON = 1;							// Habilita módulo.
    delay(1);								// Aguarda...
    ADCON0bits.GO = 1;								// Inicia conversão.
    while(ADCON0bits.GO);							// Aguarda terminar a conversão.
#elif   _PIC18
    ADCON0 = 0x00;								// Canal AN0 selecionado.
    ADCON0bits.ADON = 1;							// Habilita módulo.
    delay(1);								// Aguarda...
    ADCON0bits.GO = 1;								// Inicia conversão.
    while(ADCON0bits.GO);							// Aguarda terminar a conversão.
#endif
  
    adc01Temp = (unsigned) (ADRESH<<8) | ADRESL;				// Unindo as partes para compor o valor.
    return adc01Temp;								// Retorna com o valor bruto.
}

unsigned char temperaturaLer(void) 
{
    unsigned int temp01VlrInt;                                                  // Variavel local tipo inteira, não inicializada
    unsigned int temp01VlrTmp;							// Temperatura: de 0 até 150°C (Full range: de -55 a 150°C)
    temp01VlrInt = adcLer();							// Lê o resultado e...
    temp01VlrTmp =(unsigned int) (temp01VlrInt * 0.48875);                      // Converte em temperatura Celsius
    return temp01VlrTmp;
}
