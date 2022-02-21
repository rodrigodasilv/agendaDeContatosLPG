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
	char *nomePont, *texto;
	int distanciaVerifica;
	FILE *agenda = fopen("arquivo_agenda.txt", "r");
    if (agenda == NULL) pause("Erro na abertura do arquivo.\n");
    else {
        char valores[168]; 
        char tempValores[168];
        
        while(fgets(valores, sizeof(valores), agenda) != NULL){
        	if(valores[0] == '\n'){
                continue;
            }
           	strcpy(tempValores, valores); 	
		    strtok(valores,","); 
		    nomePont = strtok(NULL,",");
		    char nomeStr[14] = "";
		    strncpy(nomeStr, nomePont, 14);
		    distanciaVerifica = verificaDistancia(nomeStr,strlen(nomeStr), busca, strlen(busca));
		    if(distanciaVerifica == distancia){
			    texto = strtok(tempValores,",");
		        printf("Codigo: %s -", texto);
		        texto = strtok(NULL,",");
		        printf(" Nome:%s -", texto);
		        texto = strtok(NULL,",");
		        printf(" Email:%s -", texto);
		        texto = strtok(NULL,",");
		        printf(" Celular:%s", texto); 
			}
        }    
    fclose(agenda);
	}
}