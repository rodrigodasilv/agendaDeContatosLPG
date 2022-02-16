#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/alterar.h"

#include "../include/variaveis.h"
#include "../include/gerais.h"
#include "../include/incluir.h" // alterar_contato() usa a função pedirDadosInclusao.

// Faz a edição de um contato já existente.
void alterar_contato() {
    int id_contato = pedir_idContato();
    if (id_contato == 0) return; // O usuario decidiu voltar ao menu

    char dados[168];

    // Coleta os dados do arquivo
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        pause("Erro na abertura do arquivo.\n");
        return;
    }

    // Display dos dados pro usuario
    int id_aux = 1;
    while (fgets(dados, sizeof(dados), dados_agenda) != NULL) {
        if (id_aux == id_contato) {
            system("cls");
            printf("Dados: %s", dados);
            break;
        }
        id_aux++;
    } fclose(dados_agenda);

    char **dados_incluir = pedirDadosInclusao();
    strcpy(registro.nome, dados_incluir[0]);
    strcpy(registro.email, dados_incluir[1]);
    strcpy(registro.celular, dados_incluir[2]);
    
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    temp_agenda  = fopen("temp_agenda.txt","w+");

    // Cria uma agenda temporaria com o contato editado
    id_aux = 1;
    while (fgets(dados, sizeof(dados), dados_agenda) != NULL) {
        if(id_aux != id_contato) {
            fputs(dados, temp_agenda);
        } else {
            fprintf(temp_agenda, "%d, %s, %s, %s\n", id_contato, registro.nome, registro.email, registro.celular);
        }
        id_aux++;
    }

    // Substitui a nova agenda pela agenda antiga
    fclose(dados_agenda);
    fclose(temp_agenda);
    if (remove("arquivo_agenda.txt") != 0) perror("Erro");
    rename("temp_agenda.txt", "arquivo_agenda.txt");
}    

// Faz a validacao do input do usuário.
// Retorna 0 se o usuário decidir voltar ao menu.
// Retorna o próprio id do contato, se for validado.
int pedir_idContato() {
    int id_contato;
    do {
        printf("Digite 0 para voltar ao menu.\nID do registro: ");
        scanf(" %i", &id_contato);
        limpar_buffer();
        
        if (id_contato == 0)             // Voltar para o menu
            return 0;
        else if (editar_aux(id_contato)) // Opcao validada
            return id_contato;
        else {                           // Opcao invalida
            clear();
            printf("ID invalido.\n");
        }
    } while (editar_aux(id_contato) != 1);
    return 0;
}

/*
Auxilia a função editar contato. 
Retorna 0 se o contato não existe; 
Retorna 1 se o contato existe.
*/
int editar_aux(int input) {
    char dados[168];
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    while (fgets(dados, sizeof(dados), dados_agenda) != NULL) {
        if (dados[0] == '\n') // Linha vazia (contato deletado)
            continue;
        else if (atoi(dados) == input) {
            fclose(dados_agenda);
            return 1;
        }
    }
    fclose(dados_agenda);
    return 0;
}