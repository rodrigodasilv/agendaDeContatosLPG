#include <stdio.h>
#include <stdlib.h>

#include "../include/excluir.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"

// Exclui o contato pelo id, se tal id existir.
void excluir_contato(void){
	int id_contato; 
	char conteudo[168]; 
	int linha = 1;
	int aux_excluido=0;
    int retorno;
	printf("Informe o codigo do contato para excluir: ");
	scanf("%d",&id_contato);
	limpar_buffer();
    clear();

    retorno = confere_excluido(id_contato);
    
    if(retorno == 2){ // A agenda nao abriu na funcao confere_excluido
        pause("Erro na abertura do arquivo.\n");
        return;
    } else if (retorno == 1) { // O contato ja foi excluido (linha vazia)
        pause("Contato ja excluido!\n");
    } else if(retorno == 0){
        dados_agenda = fopen("arquivo_agenda.txt","r+");
	    temp_agenda  = fopen("temp_agenda.txt","w+");
	
        if (dados_agenda == NULL) {
            pause("Erro na abertura do arquivo.\n");
        } else {
            printf("Arquivo aberto.\n");
            while(fgets (conteudo, sizeof(conteudo), dados_agenda)) {
                if(linha != id_contato){ 
                    fputs(conteudo,temp_agenda);
                }else{
                    fputs("\n",temp_agenda);
                    aux_excluido=1;
                }
                linha++;
            }      
        }
        fclose(dados_agenda);
        fclose(temp_agenda);
        remove("arquivo_agenda.txt");
        rename("temp_agenda.txt", "arquivo_agenda.txt");
        if (aux_excluido==1){
            pause("Contato Excluido!\n");	
        }else{
            pause("Erro ao excluir: contato nao encontrado!\n");
        }
    }
}

/*
A função confere_excluido auxilia a função excluir_contato.
Retorna 0 se chamar um id que não foi excluído.
Retorna 1 se chamar um id que já foi excluído.
Retorna 2 se deu erro na abertura da agenda.
*/
int confere_excluido(int id) {
    char conteudo[168]; 
	int linha = 1;
    int teste_conteudo = 0;

    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        teste_conteudo = 2;
    } else {
        while(fgets (conteudo, 168, dados_agenda) != NULL) {
            if(conteudo[0] == '\n' && linha == id){
                teste_conteudo = 1;
                break; 
            }
            linha++;
        }    
    }
    fclose(dados_agenda);
    return teste_conteudo;  
}
