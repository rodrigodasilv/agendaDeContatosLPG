#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/excluir.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"

// Exclui o contato pelo id, se tal id existir.
void excluir_contato(void){
    if(testar_agenda("arquivo_agenda.txt") == 0) return;
    if(testar_agenda("temp_agenda.txt") == 0) return;

	int id_contato;
	printf("ID do registro: ");
	scanf("%d",&id_contato);
	limpar_buffer();
    clear();

    int retorno = contato_existe(id_contato);
    if (retorno == 0) pause("Erro: ID Invalido\n");
    else if(retorno == 1){
        char *conteudo = extrair_dados("arquivo_agenda.txt")[id_contato-1];
        registro = str_to_contato(conteudo);

        inserir_dados("arquivo_agenda.txt", registro, 0); // O zero sinaliza a exclusao do id

        // Verifica se o contato foi realmente excluido (Redundancia)
        if (agenda_vazia("arquivo_agenda.txt") == 0) {
            pause("A agenda agora esta vazia.\n");
        } else{
            conteudo = extrair_dados("arquivo_agenda.txt")[id_contato-1];
            if (*conteudo == 0) pause("Contato Excluido!\n");	
            else pause("Erro ao excluir!\n");
        }
    }
}