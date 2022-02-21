#include <stdio.h>
#include <locale.h>

#include "include/gerais.h"
#include "include/variaveis.h"

#include "include/incluir.h"
#include "include/excluir.h"
#include "include/alterar.h"
#include "include/listar.h"
#include "include/localizar.h"

void menuPrincipal(int itemMenu);

int main() {
	setlocale(LC_ALL, "");
	menuPrincipal(0);
	return 0;
}

void menuPrincipal(int itemMenu){
    clear();

    printf("                              __      \n");   
    printf("  ____ _____ ____  ____  ____/ /___ _ \n"); 
    printf(" / __ `/ __ `/ _ \\/ __ \\/ __  / __ `/ \n");
    printf("/ /_/ / /_/ /  __/ / / / /_/ / /_/ /  \n");
    printf("\\__,_/\\__, /\\___/_/ /_/\\__,_/\\__,_/   \n");
    printf("     /____/                           \n");
    printf("\nInforme a operacao desejada: \n1) Incluir um novo contato; \n2) Excluir um contato existente; \n");
    printf("3) Alterar um contato existente; \n4) Listar todos os contatos cadastrados; \n5) Localizar um contato.\n");
    printf("6) Encerrar execucao.\n\nInput: ");
    scanf(" %d",&itemMenu);
    limpar_buffer();
    
    clear();
	switch (itemMenu){
		case 1: {   
            incluir_contato();     
        } break;
        case 2: {
            excluir_contato();
        } break;    
        case 3: {
            alterar_contato();   
        } break;
        case 4: {
            listar_contatos();   
        } break;
        case 5: {
            localizar_contatos();  
        } break;
        case 6: {
            return; // Encerra o programa
        }
		default: {
            pause("Input invalido!\n");
            clear();
        } break;
	}
    menuPrincipal(itemMenu);
}