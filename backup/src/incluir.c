#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/incluir.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"

// Inclui os dados coletados da função pedirDadosInclusao() no arquivo_agenda.txt
void incluir_contato(){
    dados_agenda = fopen("arquivo_agenda.txt", "a+");

    if (dados_agenda == NULL) {
        pause("Erro na abertura do arquivo.\n");
        return;
    } else {
        printf("Arquivo aberto.\n\n");

        char **dados_incluir = pedirDadosInclusao();
        registro.cod = contar_linhas();
        strcpy(registro.nome, dados_incluir[0]);
        strcpy(registro.email, dados_incluir[1]);
        strcpy(registro.celular, dados_incluir[2]);
        clear();

        fprintf(dados_agenda, "%d, %s, %s, %s\n", registro.cod, registro.nome, registro.email, registro.celular); //Essa parte registra no arquivo
        printf("%d, %s, %s, %s\n\n", registro.cod, registro.nome, registro.email, registro.celular); //Essa parte faz o display
    }
    fclose(dados_agenda);

    pause("Contato Salvo!\n");
}

// Faz a contagem da quantidade de linhas.
// É usada para definir o próximo id.
int contar_linhas(void) {
    char conteudo; 
    char letra = '\n';
    int contador = 1;

    while(fread (&conteudo, sizeof(char), 1, dados_agenda)) {
            if(conteudo == letra) {
                contador++;
            }
        } 
    return contador;
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
Essa função é utilizada em incluir_contato e alterar_contato.
*/
char **pedirDadosInclusao(void) {
    // Armazena os ponteiros das strings, serve para que a função possa "retornar uma array"
    char **dadosInclusao = malloc(3 * sizeof(char *));
    dadosInclusao[0] = myFgets("Digite o nome: ", 50);
    do{   dadosInclusao[1] = myFgets("Digite um email: ", 100);   }while(validar_email(dadosInclusao[1]) != 1);
    dadosInclusao[2] = myFgets("Digite o numero de celular: ", 14);

    return dadosInclusao;
}