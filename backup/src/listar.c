#include <stdio.h>
#include <string.h>

#include "../include/listar.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"

// Lista no terminal todos os contatos da agenda.
void listar_contatos(void){
    char *texto;
    int retorno = 1;
    int vazio = 0;
    
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        pause("Erro na abertura do arquivo.\n");
    } else {
        printf("Arquivo aberto.\n\n");
        char linha[168]; //168 porque e o numero de bytes no resgitro
        
        while(fgets(linha, sizeof(linha), dados_agenda) != NULL){
            if(linha[0] == '\n'){
                continue;
            }
            texto = strtok(linha,",");
            printf("Codigo: %s -", texto);
            texto = strtok(NULL,",");
            printf(" Nome:%s -", texto);
            texto = strtok(NULL,",");
            printf(" Email:%s -", texto);
            texto = strtok(NULL,",");
            printf(" Celular:%s", texto);  

            vazio = 1; 
        }    
    }
    retorno = fclose(dados_agenda); // Se o arquivo foi fechado corretamente, entao retorna 0
    if(retorno == 0 && vazio == 0){ 
        pause("Sem contatos armazenados!\n"); //<-- se o arquivo existe e todos os contatos foram excluidos
    }
    pause("\n\n");
}