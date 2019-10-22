
#include <pic16f887.h>
#include "config.h"
#include "delay.h"
 void ADC_inicializar(void) // Sub rotina de inicialização do ADC.
 {
 // Configura INT do ADC:
 ADIF = 0; // Limpa Flag
 ADIE = 0; // Desliga a interrupção.

 TRISA = TRISA | 0x03; // AN0/AN1 como entrada.
 ANSEL = 0x03; // AN0/AN1 como analógico.
 // Configurar o módulo:
 ADCON1 = 0b10000000; // Just Right, Seleciona Vref(0 e 5V).
 ADCON0 = 0b10000001; // FOSC/32, Seleciona canal, Sem habilitação do ADC.
 delay(1); // Aguarda...
 }

 unsigned int ADC_canal0(void) // Função de seleção e leitura do módulo.
 {
 unsigned int temp; // Variável local temporária.
 ADCON0  = 0x80; // Canal AN0 selecionado.
 ADCON0bits.ADON = 1; // Habilita módulo.
 delay(1); // Aguarda...
 ADCON0bits.GO = 1; // Inicia conversão.
 while(ADCON0bits.GO); // Aguarda terminar a conversão.
 temp = (ADRESH<<8) | ADRESL; // Unindo as partes para compor o valor.
 return temp; // Retorna com o valor bruto.
 }

