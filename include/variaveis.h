#ifndef VARIAVEIS_H
#define VARIAVEIS_H

#include <stdio.h>

typedef struct{
 	int   cod;
	char  nome[50];
	char  email[100];
	char  celular[15];
} Contato;
extern Contato registro;

#endif
