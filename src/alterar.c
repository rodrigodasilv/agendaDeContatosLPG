#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/alterar.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"
#include "../include/incluir.h" // alterar_contato() usa a função pedirDadosInclusao.

// Faz a edição de um contato já existente.
void alterar_contato() {
    if(testar_agenda("arquivo_agenda.txt") == 0) return;
    if(testar_agenda("temp_agenda.txt") == 0) return;

    int id_contato;
    printf("ID do registro: ");
    scanf(" %i", &id_contato);
    limpar_buffer();
    clear();

    int retorno = contato_existe(id_contato);
    if (retorno == 0) pause("Erro: ID Invalido\n");
    else {
        registro.cod = id_contato;
        char **dados_atuais = extrair_dados("arquivo_agenda.txt");

        printf("Dados: %s\n", dados_atuais[registro.cod - 1]);

        char **dados_incluir = pedirDadosInclusao();
        strcpy(registro.nome, dados_incluir[0]);
        strcpy(registro.email, dados_incluir[1]);
        strcpy(registro.celular, dados_incluir[2]);

        inserir_dados("arquivo_agenda.txt", registro, 1);
    }
}