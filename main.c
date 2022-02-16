#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

FILE *dados_agenda;
FILE *temp_agenda;
int itemMenu;

void clear(void);
void pause(char *mensagem);
char *myFgets(char mensagem[], int tamanho);
char **pedirDadosInclusao(void);
void incluir_dados(void);
int contar_linhas(void);
void limpar_buffer(void);
int validar_email(char* email_input);
void excluir_contato(void);
void listar_contatos(void);
int confere_excluido(int);
int pedir_idContato(void);
void editar_contatos(void);
void localizar_contatos(void);
int editar_aux(int);
int verificaDistancia(char[], int, char[], int);
int min(int, int, int);
void printa_na_tela(int, char[]);

typedef struct{
 	int   cod;
	char  nome[50];
	char  email[100];
	char  celular[14];
} Contato;
Contato registro;

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
            incluir_dados();     
        } break;
        case 2: {
            excluir_contato();
        } break;    
        case 3: {
            editar_contatos();   
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

// Limpa o terminal.
void clear() { system("cls"); }

// Imprime uma mensagem personalizada e faz o programa ficar parado ate que seja pressionado ENTER.
void pause(char *mensagem) {
    printf("%sPressione ENTER para continuar.", mensagem);
    getchar();
}

// Faz um fgets removendo a quebra de linha automática da função.
char *myFgets(char mensagem[], int tamanho) {
    char *input = malloc(tamanho * sizeof(char));
    printf("%s", mensagem);
    fgets(input, tamanho, stdin);
    input[strcspn(input, "\n")] = 0; // Remove a quebra de linha
    return input;
}

/*
Faz o diálogo que pede para o usuário os dados a ser cadastrados.
Essa função é utilizada em incluir_dados e editar_contatos.
*/
char **pedirDadosInclusao(void) {
    // Armazena os ponteiros das strings, serve para que a função possa "retornar uma array"
    char **dadosInclusao = malloc(3 * sizeof(char *));
    dadosInclusao[0] = myFgets("Digite o nome: ", 50);
    do{   dadosInclusao[1] = myFgets("Digite um email: ", 100);   }while(validar_email(dadosInclusao[1]) != 1);
    dadosInclusao[2] = myFgets("Digite o numero de celular: ", 14);

    return dadosInclusao;
}

// Inclui os dados coletados da função pedirDadosInclusao() no arquivo_agenda.txt
void incluir_dados(){
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

// Exclui o contato pelo id, se tal id existir.
void excluir_contato(void){
	int id_contato; 
	char conteudo[168]; 
	int linha = 1;
	int aux_excluido=0;
    int retorno;
	printf("Informe o codigo do contato para excluir: ");
	scanf("%d",&id_contato);
	limpar_buffer();
    clear();

    retorno = confere_excluido(id_contato);
    
    if(retorno == 2){ // A agenda nao abriu na funcao confere_excluido
        pause("Erro na abertura do arquivo.\n");
        return;
    } else if (retorno == 1) { // O contato ja foi excluido (linha vazia)
        pause("Contato ja excluido!\n");
    } else if(retorno == 0){
        dados_agenda = fopen("arquivo_agenda.txt","r+");
	    temp_agenda  = fopen("temp_agenda.txt","w+");
	
        if (dados_agenda == NULL) {
            pause("Erro na abertura do arquivo.\n");
        } else {
            printf("Arquivo aberto.\n");
            while(fgets (conteudo, sizeof(conteudo), dados_agenda)) {
                if(linha != id_contato){ 
                    fputs(conteudo,temp_agenda);
                }else{
                    fputs("\n",temp_agenda);
                    aux_excluido=1;
                }
                linha++;
            }      
        }
        fclose(dados_agenda);
        fclose(temp_agenda);
        remove("arquivo_agenda.txt");
        rename("temp_agenda.txt", "arquivo_agenda.txt");
        if (aux_excluido==1){
            pause("Contato Excluido!\n");	
        }else{
            pause("Erro ao excluir: contato nao encontrado!\n");
        }
    }
}

/*
A função confere_excluido auxilia a função excluir_contato.
Retorna 0 se chamar um id que não foi excluído.
Retorna 1 se chamar um id que já foi excluído.
Retorna 2 se deu erro na abertura da agenda.
*/
int confere_excluido(int id) {
    char conteudo[168]; 
	int linha = 1;
    int teste_conteudo = 0;

    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        teste_conteudo = 2;
    } else {
        while(fgets (conteudo, 168, dados_agenda) != NULL) {
            if(conteudo[0] == '\n' && linha == id){
                teste_conteudo = 1;
                break; 
            }
            linha++;
        }    
    }
    fclose(dados_agenda);
    return teste_conteudo;  
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

// Remove qualquer resquicio no buffer do teclado
void limpar_buffer(void) {
    char c;
    while((c = getchar()) != '\n' && c != EOF);
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

// Lista no terminal todos os contatos da agenda.
void listar_contatos(void){
    char *texto;
    int retorno = 1;
    int vazio = 0;
    
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        pause("Erro na abertura do arquivo.\n");
    } else {
        printf("Arquivo aberto.\n\n");
        char linha[168]; //168 porque e o numero de bytes no resgitro
        
        while(fgets(linha, sizeof(linha), dados_agenda) != NULL){
            if(linha[0] == '\n'){
                continue;
            }
            texto = strtok(linha,",");
            printf("Codigo: %s -", texto);
            texto = strtok(NULL,",");
            printf(" Nome:%s -", texto);
            texto = strtok(NULL,",");
            printf(" Email:%s -", texto);
            texto = strtok(NULL,",");
            printf(" Celular:%s", texto);  

            vazio = 1; 
        }    
    }
    retorno = fclose(dados_agenda); // Se o arquivo foi fechado corretamente, entao retorna 0
    if(retorno == 0 && vazio == 0){ 
        pause("Sem contatos armazenados!\n"); //<-- se o arquivo existe e todos os contatos foram excluidos
    }
    pause("\n\n");
}

// Faz as substituições entre o nome atual do arquivo e o input de busca do usuário até que ambos sejam iguais,
// em seguida, contabiliza quantas substituições foram necessárias para constatar a distância entre as palavras.
int verificaDistancia(char nome[], int tamNome, char busca[], int tamBusca){
	if (tamBusca == 0) return tamNome;
	if (tamNome == 0) return tamBusca;
    
    if (busca[tamBusca - 1] == nome[tamNome - 1]) {
        return verificaDistancia(busca, tamBusca - 1, nome, tamNome - 1);
	}

    int s = verificaDistancia(busca, tamBusca - 1, nome, tamNome - 1); 
    int r = verificaDistancia(busca, tamBusca, nome, tamNome - 1); 
    int i = verificaDistancia(busca, tamBusca - 1, nome, tamNome); 
    return min(s, r, i) + 1;
}

// Retorna o valor mínimo entre os três termos.
int min(int a, int b, int c) {
	int min = a;
	if (min > b) min = b;
	if (min > c) min = c;

	return min;
}

// Faz o print formatado e ordenado do resultado da busca.
void printa_na_tela(int distancia, char busca[]){
	char *nomePont, *codigo, *texto;
	int distanciaVerifica;
	dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        pause("Erro na abertura do arquivo.\n");
    } else {
        char valores[168]; 
        char tempValores[168];
        
        while(fgets(valores, sizeof(valores), dados_agenda) != NULL){
        	if(valores[0] == '\n'){
                continue;
            }
           	strcpy(tempValores, valores); 	
		    codigo = strtok(valores,","); 
		    nomePont = strtok(NULL,",");
		    char nomeStr[14] = "";
		    strncpy(nomeStr, nomePont, 14);
		    distanciaVerifica = verificaDistancia(nomeStr,strlen(nomeStr), busca, strlen(busca));
		    if(distanciaVerifica == distancia){
			    texto = strtok(tempValores,",");
		        printf("Codigo: %s -", texto);
		        texto = strtok(NULL,",");
		        printf(" Nome:%s -", texto);
		        texto = strtok(NULL,",");
		        printf(" Email:%s -", texto);
		        texto = strtok(NULL,",");
		        printf(" Celular:%s", texto); 
			}
        }    
    fclose(dados_agenda);
	}
}

// Faz a busca no arquivo de acordo com o nome inserido pelo usuario
void localizar_contatos(void){
	char busca[14];
	printf("Digite o nome do contato: ");
	scanf(" %s", busca);
    limpar_buffer();
    printf("\n");

	for(int i = 0; i < 5; i++){
		printa_na_tela(i, busca);
	}
    pause("\n\n");
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
    } while (id_contato != 0 || editar_aux(id_contato) != 1);
}

// Faz a edição de um contato já existente.
void editar_contatos() {
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

int main() {
	setlocale(LC_ALL, "");
	menuPrincipal(0);
	return 0;
}
