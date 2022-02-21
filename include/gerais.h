#ifndef GERAIS_H
#define GERAIS_H

#include "./variaveis.h"

void clear(void);
void pause(char *mensagem);
void limpar_buffer(void);
char *myFgets(char mensagem[], int tamanho);
int contar_linhas(char *dir, char *escolha);
int contato_existe(int id);
int testar_agenda(char* dir);
int agenda_vazia(char *dir);
Contato str_to_contato(char *string);
char **extrair_dados(char *dir_agenda);
void inserir_dados(char *dir_agenda, Contato registro, int operacao);

#endif