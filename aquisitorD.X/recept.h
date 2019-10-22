
#ifndef RECEPT_H_
#define RECEPT_H_

//Lista de declaração de funções.
	void salvatemp(unsigned char temp);
	void resetemp(void);
	unsigned char media(void);
	unsigned char moda(void);
	unsigned char mediana(void);
	void EEPROM_write(unsigned char pont,unsigned int value);
	int EEPROM_read(unsigned char pont);
    void EEPROM_WriteByte(unsigned char eepromAddress, unsigned char eepromData);
    unsigned char EEPROM_ReadByte(unsigned char eepromAddress);
    void tmron(void);
    char looptmr(void);
#endif	/* RECEPT_H_ */

