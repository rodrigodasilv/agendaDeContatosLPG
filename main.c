#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct{
 	int   cod;
	char  nome[20];
	char  mail[100];
	char  celular[14];
} contato;
int itemMenu;

void menuPrincipal(int itemMenu){
	switch (itemMenu){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			printf("                              __      \n");   
			printf("  ____ _____ ____  ____  ____/ /___ _ \n"); 
			printf(" / __ `/ __ `/ _ \\/ __ \\/ __  / __ `/ \n");
			printf("/ /_/ / /_/ /  __/ / / / /_/ / /_/ /  \n");
			printf("\\__,_/\\__, /\\___/_/ /_/\\__,_/\\__,_/   \n");
			printf("     /____/                           \n");
			printf("\nInforme a operação desejada: \n1) incluir um novo contato; \n2) excluir um contato existente; \n3) alterar um contato existente; \n4) listar todos os contatos cadastrados; \n5) localizar um contato.\n");
			scanf(" %i",&itemMenu);
			menuPrincipal(itemMenu);
	}
}

int main() {
	setlocale(LC_ALL,"");
	menuPrincipal(0);
	return 0;
}
