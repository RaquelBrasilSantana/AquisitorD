#ifndef __LEITORLM35_V07_H
#define __LEITORLM35_V07_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000                                                     // Determina cristal atual, uso obrigatorio para "delay".
#endif

void temperaturaInicializar(void);

unsigned int adcLer(void);

unsigned char temperaturaLer(void);


#endif