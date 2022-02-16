#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

FILE *dados_agenda;
FILE *temp_agenda;
int itemMenu;

void clear(void);
char *myFgets(char mensagem[], int tamanho);
char ** pedirDadosInclusao(void);
void incluir_dados();
int contar_linhas(void);
void limpar_buffer(void);
int validar_email(char* email_input);
void excluir_contato(void);
void listar_contatos(void);
int confere_excluido(int);
int validar_edicao(void);
void editar_contatos(int bool_validado);
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
    
	switch (itemMenu){
		case 1: {   
            incluir_dados();     
        } break;
        case 2: {
            excluir_contato();
        } break;    
        case 3: {
            editar_contatos(validar_edicao());   
        } break;
        case 4: {
            listar_contatos();   
        } break;
        case 5: {
            localizar_contatos();  
        } break;
        case 6: {
            return;
        }
		default: {
            printf("Input invalido!\n");  
        } break;
	}
    menuPrincipal(itemMenu);
}

// Limpa o terminal
void clear() {
    system("cls");
}

// Faz um fgets removendo a quebra de linha automática da função
char *myFgets(char mensagem[], int tamanho) {
    char *input = malloc(tamanho * sizeof(char));
    printf("%s", mensagem);
    fgets(input, tamanho, stdin);
    input[strcspn(input, "\n")] = 0; // Remove a quebra de linha
    return input;
}

// Faz o diálogo que pede para o usuário os dados a ser cadastrados
char **pedirDadosInclusao(void) {
    // Armazena os ponteiros das strings, serve para a função "retornar uma array"
    char **dadosInclusao = malloc(3 * sizeof(char *));
    limpar_buffer();
    dadosInclusao[0] = myFgets("Digite o nome: ", 50);
    do {dadosInclusao[1] = myFgets("Digite um email: ", 100);} while(validar_email(dadosInclusao[1]) != 1);
    dadosInclusao[2] = myFgets("Digite o numero de celular: ", 14);

    return dadosInclusao;
}

// Recebe um array[3] de string e inclui esses dados no arquivo_agenda.txt
void incluir_dados(){
    dados_agenda = fopen("arquivo_agenda.txt", "a+");

    if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return;
    } else {
        printf("Arquivo aberto.\n");

        char **dados_incluir = pedirDadosInclusao();
        registro.cod = contar_linhas();
        strcpy(registro.nome, dados_incluir[0]);
        strcpy(registro.email, dados_incluir[1]);
        strcpy(registro.celular, dados_incluir[2]);

        fprintf(dados_agenda, "%d, %s, %s, %s\n", registro.cod, registro.nome, registro.email, registro.celular); //Essa parte registra no arquivo
    }
    fclose(dados_agenda);

    printf("Contato Salvo!");
    printf("\nPressione qualquer tecla para finalizar.");
    getchar();
}

void excluir_contato(void){
	int id_contato; 
	char conteudo[168]; 
	int linha = 1;
	int aux_excluido=0;
    int retorno;
	printf("Informe o codigo do contato para excluir: \n");
	scanf("%d",&id_contato);
	limpar_buffer();

    retorno = confere_excluido(id_contato);
    
    if(retorno == 2){
        printf("\nPressione qualquer tecla para finalizar.\n");
        getchar();
        return;
    }
	
    if(retorno == 0){
        dados_agenda = fopen("arquivo_agenda.txt","r+");
	    temp_agenda  = fopen("temp_agenda.txt","w+");
	
        if (dados_agenda == NULL) {
            printf("Erro na abertura do arquivo.\n");
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
            printf("Contato Excluido!");	
        }else{
            printf("Erro ao excluir: contato nao encontrado!\n");
        }
    } else {
        printf("Contato ja excluido!\n");
    } 
    printf("\nPressione qualquer tecla para finalizar.\n");
    getchar();
}

//A função confere_excluido auxilia a função excluir_contato,
//se chamar um id para exclusão que já foi excluido ira retornar 1
int confere_excluido(int id) {
    char conteudo[168]; 
	int linha = 1;
    int teste_conteudo = 0;

    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n"); 
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
    printf("Email invalido!\n");
    return 0;
}

void listar_contatos(void){
    char *texto;
    int retorno = 1;
    int vazio = 0;
    
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
    } else {
        printf("Arquivo aberto.\n");
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
    retorno = fclose(dados_agenda); // Se o arquivo � fechado corretamente, ent�o retorna 0
    if(retorno == 0 && vazio == 0){ 
        printf("Sem contatos armazenados!\n"); //<-- se arquivo existe e todos os contatos foram excluidos
    }
    limpar_buffer();
    printf("\nPressione qualquer tecla para finalizar.");
    getchar();   
}

void localizar_contatos(void){
	char busca[14];
	printf("Digite o nome do contato :");
	scanf("%s", busca);
	for(int i = 0; i < 6; i++){
		printa_na_tela(i, busca);
	} 
}

int verificaDistancia(char nome[], int tamB,char busca[], int tamA){

	if (tamA == 0) return tamB;
	if (tamB == 0) return tamA;
    
    if (busca[tamA - 1] == nome[tamB - 1]) {
        return verificaDistancia(busca, tamA - 1, nome, tamB - 1);
	}

    int s = verificaDistancia(busca, tamA - 1, nome, tamB - 1); 
    int r = verificaDistancia(busca, tamA, nome, tamB - 1); 
    int i = verificaDistancia(busca, tamA - 1, nome, tamB); 
    return min(s, r, i) + 1;
}

// Retorna o valor mínimo entre os termos
int min(int a, int b, int c) {
	int min = a;
	if (min > b) min = b;
	if (min > c) min = c;

	return min;
}

void printa_na_tela(int distancia, char busca[]){
	char *nomePont, *codigo, *texto;
	int distanciaVerifica;
	dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
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

// Faz a validacao do input do usuário.
int validar_edicao() {
    int id_contato;
    do {
        printf("Digite 0 para voltar ao menu.\nID do registro: ");
        scanf(" %i", &id_contato);
        
        if (id_contato == 0)             // Voltar para o menu
            return 0;
        else if (editar_aux(id_contato)) // Opcao validada
            return 1;
        else {                           // Opcao invalida
            clear();
            printf("ID invalido.\n");
        }
    } while (id_contato != 0 || editar_aux(id_contato) != 1);
}
// Faz a edição de um contato já existente.
void editar_contatos(int bool_validado) {
    if (bool_validado == 0) return; // O usuario decidiu voltar ao menu

    int id_contato;
    char dados[168];

    // Coleta os dados do arquivo
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
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
