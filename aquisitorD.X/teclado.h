#ifndef __TECLADO4X4_V07_H
#define __TECLADO4X4_V07_H

#define tecL1 PORTBbits.RB0				// Pino da Coluna 1
#define tecL2 PORTBbits.RB1				// Pino da Coluna 2
#define tecL3 PORTBbits.RB2				// Pino da Coluna 3
#define tecL4 PORTBbits.RB3				// Pino da Coluna 4
#define tecC1 PORTBbits.RB4				// Pino da Linha 1
#define tecC2 PORTBbits.RB5				// Pino da Linha 2
#define tecC3 PORTBbits.RB6				// Pino da Linha 3
#define tecC4 PORTBbits.RB7				// Pino da Linha 4
#define cfgSaidaTEC TRISB				// Configura��o das entradas(1) e sa�das(0).

#ifndef _PIC16								// Se for para 16F...
#define Saida PORTB							// ...define o termo correto para a sa�da.
#elif   _PIC18								// Se for para 18F...
#define Saida LATB							// ...define o termo correto para a sa�da.
#endif

unsigned char tecAnterior;					// Vari�vel local, armazena valor antigo.
unsigned char tecAtual;					// Vari�vel local, armazena valor novo.

const unsigned char tabTeclas[]={'1','4','7','F','2','5','8','0','3','6','9','E','A','B','C','D'};

void tecladoIniciar(void)
{
#ifndef _PIC16									// Se for para 16F...
	OPTION_REGbits.nRBPU=0;							// Ativa os resistores de Pull-Up no PORTB
	ANSELH=0x00;								// Desliga entrada anal�gica
#elif   _PIC18									// Se for para 18F...
	INTCON2bits.RBPU=0;							// Ativa os resistores de Pull-Up no PORTB
	ADCON1 |= 0x0E;								// Desliga entrada anal�gica
#endif
	cfgSaidaTEC=0B00001111;							// RB7-RB4: Input(Entrada=1)  RB3-RB0: Output (Sa�da=0)
	Saida=0x00;								// Limpa o PORTB.
	tecAnterior=0x00;							// Limpa a vari�vel local.
	tecAtual=0x00;							// Limpa a vari�vel local.
}

unsigned char tecladoLer(void)							// Loop infinito. Inicio...
{
    tecC4=1,tecC3=1,tecC2=1,tecC1=0;					// Ativa somente a 1� coluna.
    NOP();NOP();								// NOP=Sem opera��o. Perde tempo para estabilizar.
    if(!tecL1)	tecAtual = tabTeclas[0];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tecL2)	tecAtual = tabTeclas[1];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tecL3)	tecAtual = tabTeclas[2];				// Se a terceira linha for ativada, guardar este caracter.
    else if(!tecL4)	tecAtual = tabTeclas[3];				// Se a quarta linha for ativada, guardar este caracter.

    tecC4=1,tecC3=1,tecC2=0,tecC1=1;					// Ativa somente a 2� coluna.
    NOP();NOP();								// NOP=Sem opera��o. Perde tempo para estabilizar.
    if(!tecL1)	tecAtual = tabTeclas[4];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tecL2)	tecAtual = tabTeclas[5];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tecL3)	tecAtual = tabTeclas[6];				// Se a terceira linha for ativada, guardar este caracter
    else if(!tecL4)	tecAtual = tabTeclas[7];				// Se a quarta linha for ativada, guardar este caracter.
    
    tecC4=1,tecC3=0,tecC2=1,tecC1=1;					// Ativa somente a 3� coluna.
    NOP();NOP();								// NOP=Sem opera��o. Perde tempo para estabilizar.
    if(!tecL1)	tecAtual = tabTeclas[8];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tecL2)	tecAtual = tabTeclas[9];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tecL3)	tecAtual = tabTeclas[10];				// Se a terceira linha for ativada, guardar este caracter
    else if(!tecL4)	tecAtual = tabTeclas[11];				// Se a quarta linha for ativada, guardar este caracter.
    
    tecC4=0,tecC3=1,tecC2=1,tecC1=1;					// Ativa somente a 4� coluna.
    NOP();NOP();								// NOP=Sem opera��o. Perde tempo para estabilizar.
    if(!tecL1)	tecAtual = tabTeclas[12];				// Se a primeira linha for ativada, guardar este caracter.
    else if(!tecL2)	tecAtual = tabTeclas[13];				// Se a segunda linha for ativada, guardar este caracter.
    else if(!tecL3)	tecAtual = tabTeclas[14];				// Se a terceira linha for ativada, guardar este caracter
    else if(!tecL4)	tecAtual = tabTeclas[15];				// Se a quarta linha for ativada, guardar este caracter.

    // C�digo anti-repeti��o
    if(tecAtual!=tecAnterior)						// Verifica se a tecla atual � diferente da anterior...
    {
        tecAnterior=tecAtual;						// ...se for salva atual e ... 
        return tecAtual;							// ...retorna com o novo valor...
    }
    else									// ...se n�o...
    {
	tecAtual=0x00;							// Salva como n�o acionada ou n�o liberada.
        return tecAtual;							// ...retorna com o valor.
    }
}

#endif