#ifndef VARIAVEIS_H
#define VARIAVEIS_H

#include <stdio.h>

FILE *dados_agenda; // Agenda de contatos
FILE *temp_agenda;  // Agenda temporária pra fazer operações em cima da agenda original

typedef struct{
 	int   cod;
	char  nome[50];
	char  email[100];
	char  celular[14];
} Contato;
Contato registro;

#endif