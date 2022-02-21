#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/gerais.h"

#include "../include/variaveis.h"

// Limpa o terminal.
void clear() { system("cls"); }

// Imprime uma mensagem personalizada e faz o programa ficar parado ate que seja pressionado ENTER.
void pause(char *mensagem) {
    printf("%sPressione ENTER para continuar.", mensagem);
    getchar();
}

// Remove qualquer resquicio no buffer do teclado
void limpar_buffer(void) {
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

// Faz um fgets removendo a quebra de linha automática da função.
// Usado no pedirDadosInclusao() na parte de incluir contato.
char *myFgets(char mensagem[], int tamanho) {
    char *input = malloc(tamanho * sizeof(char));
    printf("%s", mensagem);
    fgets(input, tamanho, stdin);
    input[strcspn(input, "\n")] = 0; // Remove a quebra de linha
    return input;
}

/*
Faz a contagem da quantidade de linhas definida pelo parametro escolha.
Escolhas:
full -> Conta todas as linhas
vago -> Conta até o id vago
sobrando -> Conta quantas linhas estão vazias no final do txt
usadas -> Conta quantas linhas estão sendo efetivamente usadas
*/
int contar_linhas(char *dir, char *escolha) {
    int contador = 1;

    FILE *agenda = fopen(dir, "r");

    if (strcmp(escolha, "full") == 0) {
        char conteudo;
        while(fread (&conteudo, sizeof(char), 1, agenda)){
            if (conteudo == '\n') contador++;
        }
    } else if (strcmp(escolha, "vago") == 0) {
        char dados[168];
        while(fgets (dados, sizeof(dados), agenda) != NULL){
            if (dados[0] != '\n') contador++;
            else break;
        }
    } else if (strcmp(escolha, "sobrando") == 0) {
        char dados[168];
        while(fgets (dados, sizeof(dados), agenda) != NULL){
            if (dados[0] == '\n') contador++;
            else if (dados[0] != '\n') contador = 1;
        }
    } else if (strcmp(escolha, "usadas") == 0) {
        fclose(agenda);
        contador = contar_linhas(dir, "full") - contar_linhas(dir, "sobrando");
    } else {
        pause("Opcao de contagem de linhas invalida.");
        return 0;
    }
    
    fclose(agenda);
    return contador;
}

/*
Auxilia a função excluir_contato e editar_contato. 
Retorna 0 se o contato não existe; 
Retorna 1 se o contato existe.
*/
int contato_existe(int id) {
    int teste_conteudo = 1;
    int tamanho = contar_linhas("arquivo_agenda.txt", "usadas");
    if ((id > tamanho) || (id <= 0)) return 0;
    char *conteudo = extrair_dados("arquivo_agenda.txt")[id-1];

    if(strcmp(conteudo, "\n") == 0 || strcmp(conteudo, "\r") == 0 || strcmp(conteudo, "\0") == 0) teste_conteudo = 0;
    return teste_conteudo;
}

/*
Testa a abertura da agenda e imprime uma mensagem caso dê errado.
Retorna 0 se der erro na abertura e 1 se a abertura for bem-sucedida.
Serve para verificar se tem algum problema com o arquivo antes do input do usuário.
*/
int testar_agenda(char* dir) {
    FILE *agenda = fopen(dir, "a+");
    if (agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
        pause("Verifique se o programa tem permissao.\n");
        return 0;
    } fclose(agenda);
    return 1;
}

int agenda_vazia(char *dir) {
    int vazio = 0;
    if ((contar_linhas(dir, "full") == contar_linhas(dir, "sobrando")) || contar_linhas(dir, "usadas") == 0) vazio = 1;
    return vazio;
}

// Converte uma string csv para um type Contato.
Contato str_to_contato(char *string) {
    Contato registro;
    char *token;

    token = strtok(string, ",");
    registro.cod = atoi(token);
    token = strtok(NULL, ",");
    strcpy(registro.nome, token);
    token = strtok(NULL, ",");
    strcpy(registro.email, token);
    token = strtok(NULL, ",");
    strcpy(registro.celular, token);

    return registro;
}

// Puxa os dados da agenda e guarda em uma array de strings.
char **extrair_dados(char *dir_agenda) {
    char dados[168]; // Tamanho da linha
    int linhas = contar_linhas(dir_agenda, "usadas");
    char **array_dados = malloc(linhas * sizeof(dados));

    FILE *agenda = fopen(dir_agenda, "r");
    if (agenda == NULL) {
        pause("Erro na abertura do arquivo.\n");
        return NULL;
    }

    int i = 0;
    while (fgets(dados, sizeof(dados), agenda) != NULL) {
        dados[strcspn(dados, "\n")] = 0; // Remove a quebra de linha
        array_dados[i] = strdup(dados);
        i++;
        if (contar_linhas(dir_agenda, "usadas") == i) break;
    } fclose(agenda);

    return array_dados;
}

/*
Faz a inserção de um certo contato na agenda.
char *dir_agenda -> diretório do arquivo.
int operacao -> 0 para excluir, 1 para adicionar.
*/
void inserir_dados(char* dir_agenda, Contato registro, int operacao) {
    FILE *agenda = fopen(dir_agenda, "a+");
    FILE *temp_agenda = fopen("temp_agenda.txt", "w+");

    if (agenda == NULL || temp_agenda == NULL) {
        pause("Erro na abertura do arquivo.\n");
        return;
    }

    int linhas_usadas = contar_linhas(dir_agenda, "usadas");
    // Cria uma agenda temporaria com o contato editado
    if(contar_linhas(dir_agenda, "full") <= 2) fputs("\n", agenda);
    int id_aux = 1;
    char dados[168]; // Tamanho da linha
    while (fgets (dados, sizeof(dados), agenda) != NULL) {
        if(id_aux != registro.cod) fprintf(temp_agenda, "%s", dados);
        else if (id_aux == registro.cod) {
            if (operacao == 0) fputs("\n", temp_agenda);
            else fprintf(temp_agenda, "%d, %s, %s, %s\n", registro.cod, registro.nome, registro.email, registro.celular);
        }
        // Ajusta quantas linhas vazias têm no final do arquivo
        if ((linhas_usadas + 1 == id_aux) && (agenda_vazia("arquivo_agenda.txt") == 0)) break;
        id_aux++;
    } fprintf(temp_agenda, "\n"); //Sempre põe uma linha vazia
    
    fclose(agenda);
    fclose(temp_agenda);
    // Substitui a nova agenda pela agenda antiga
    if (remove("./arquivo_agenda.txt") != 0) perror("Erro");
    rename("./temp_agenda.txt", "./arquivo_agenda.txt");

    if (operacao != 0) { // Display da adição de contato 
        printf("%d, %s, %s, %s\n\n", registro.cod, registro.nome, registro.email, registro.celular); //Essa parte faz o display
        pause("Contato Salvo!\n");
    }
}