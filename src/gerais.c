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
char *myFgets(char mensagem[], int tamanho) {
    char *input = malloc(tamanho * sizeof(char));
    printf("%s", mensagem);
    fgets(input, tamanho, stdin);
    input[strcspn(input, "\n")] = 0; // Remove a quebra de linha
    return input;
}