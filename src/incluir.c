#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/incluir.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"

// Inclui os dados coletados da função pedirDadosInclusao() no arquivo_agenda.txt
void incluir_contato(){
    if(testar_agenda("arquivo_agenda.txt") == 0) return;
    if(testar_agenda("temp_agenda.txt") == 0) return;

    char **dados_incluir = pedirDadosInclusao();
    registro.cod = contar_linhas("arquivo_agenda.txt", "vago");
    strcpy(registro.nome, dados_incluir[0]);
    strcpy(registro.email, dados_incluir[1]);
    strcpy(registro.celular, dados_incluir[2]);
    clear();

    inserir_dados("arquivo_agenda.txt", registro, 1);
}

// Verifica se o input do usuário tem o "@".
// Retorna 1 para válido, e 0 para inválido.
int validar_email(char *email_input){
    int tamanho=strlen(email_input);

    for(int i = 0; i < tamanho; i++){
        char caracter = email_input[i];
        if(caracter == '@')
            return 1;
    }
    printf("Email invalido!\n\n");
    return 0;
}

/*
Faz o diálogo que pede para o usuário os dados a ser cadastrados.
Essa função é utilizada em incluir_contato() e alterar_contato().
*/
char **pedirDadosInclusao(void) {
    // Armazena os ponteiros das strings, serve para que a função possa "retornar uma array"
    char **dadosInclusao = malloc(3 * sizeof(char *));
    dadosInclusao[0] = myFgets("Digite o nome: ", 30);
    do {
        dadosInclusao[1] = myFgets("Digite um email: ", 50);
    } while(validar_email(dadosInclusao[1]) != 1);
    dadosInclusao[2] = myFgets("Digite o numero de celular: ", 14);

    clear();
    return dadosInclusao;
}
