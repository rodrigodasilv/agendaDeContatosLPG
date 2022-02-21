#include <stdio.h>
#include <string.h>

#include "../include/localizar.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"

// Faz a busca no arquivo de acordo com o nome inserido pelo usuario
void localizar_contatos(void){
	if(testar_agenda("arquivo_agenda.txt") == 0) return;
	
	char busca[14];
	printf("Digite o nome do contato: ");
	scanf(" %s", busca);
    limpar_buffer();
    printf("\n");

	for(int i = 0; i < 5; i++){
		printa_na_tela(i, busca);
	}
    pause("\n\n");
}

// Faz as substituições entre o nome atual do arquivo e o input de busca do usuário até que ambos sejam iguais,
// em seguida, contabiliza quantas substituições foram necessárias para constatar a distância entre as palavras.
int verificaDistancia(char nome[], int tamNome, char busca[], int tamBusca){
	if (tamBusca == 0) return tamNome;
	if (tamNome == 0) return tamBusca;
    
    if (busca[tamBusca - 1] == nome[tamNome - 1]) {
        return verificaDistancia(busca, tamBusca - 1, nome, tamNome - 1);
	}

    int s = verificaDistancia(busca, tamBusca - 1, nome, tamNome - 1); 
    int r = verificaDistancia(busca, tamBusca, nome, tamNome - 1); 
    int i = verificaDistancia(busca, tamBusca - 1, nome, tamNome); 
    return min(s, r, i) + 1;
}

// Retorna o valor mínimo entre os três termos.
int min(int a, int b, int c) {
	int min = a;
	if (min > b) min = b;
	if (min > c) min = c;

	return min;
}

// Faz o print formatado e ordenado do resultado da busca.
void printa_na_tela(int distancia, char busca[]){
	char *nomeStr;
	int distanciaVerifica;
	FILE *agenda = fopen("arquivo_agenda.txt", "r");
    if (agenda == NULL) pause("Erro na abertura do arquivo.\n");
    else {
        int max = contar_linhas("arquivo_agenda.txt", "usadas");
        char **conteudo = extrair_dados("arquivo_agenda.txt");
        Contato registro;

        char tempValores[168];
        for (int i = 0; i < max; i++){
        	if(conteudo[i][0] == '\n') continue;

           	strcpy(tempValores, conteudo[i]); 	
		    strtok(conteudo[i],","); 
		    nomeStr = strtok(NULL,",");
		    distanciaVerifica = verificaDistancia(nomeStr,strlen(nomeStr), busca, strlen(busca));
		    if(distanciaVerifica == distancia){
				registro = str_to_contato(tempValores);
		        printf("Codigo: %i -", registro.cod);
                printf(" Nome:%s -", registro.nome);
                printf(" Email:%s -", registro.email);
                printf(" Celular:%s", registro.celular);
			}
        } fclose(agenda);
	}
}
