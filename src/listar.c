#include <stdio.h>
#include <string.h>

#include "../include/listar.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"

// Lista no terminal todos os contatos da agenda.
void listar_contatos(void){
    if(testar_agenda("arquivo_agenda.txt") == 0) return;
    
    if (agenda_vazia("arquivo_agenda.txt") == 1) {
        printf("Sem contatos armazenados!");
    } else {
        int max = contar_linhas("arquivo_agenda.txt", "usadas");
        char **conteudo = extrair_dados("arquivo_agenda.txt");
        Contato registro;
        for (int i = 0; i < max; i++) {
            if(conteudo[i][0] != '\n'){
                registro = str_to_contato(conteudo[i]);
                printf("Codigo: %i -", registro.cod);
                printf(" Nome:%s -", registro.nome);
                printf(" Email:%s -", registro.email);
                printf(" Celular:%s", registro.celular);
            }
        }
    }
    pause("\n\n");
}
