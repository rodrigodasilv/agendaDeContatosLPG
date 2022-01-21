#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

FILE *dados_agenda;
FILE *temp_agenda;
int itemMenu;

void incluir_dados(void);
int contar_linhas(void);
void limpar_buffer(void);
char* validar_email(void);
void excluir_contato(void);
void listar_contatos(void);
int confere_excluido(int);
void editar_contatos(void);
int editar_aux(int);

typedef struct{
 	int   cod;
	char  nome[50];
	char  email[100];
	char  celular[14];
} contato;
contato registro;

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
    scanf("%d",&itemMenu);
    
    
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


void incluir_dados(void){
    dados_agenda = fopen("arquivo_agenda.txt", "a+");

    if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
        
    } else {
        printf("Arquivo aberto.\n");

        registro.cod = contar_linhas(); 

        printf ("Digite o nome: ");
        limpar_buffer();
        scanf(" %[^\n]%*c", registro.nome);
        
        validar_email();
        
        printf ("Digite o numero de celular: ");
        scanf(" %[^\n]%*c", registro.celular);

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

char* validar_email(void){
    printf("Digite um email: ");
    scanf(" %[^\n]%*c", registro.email);

    int tamanho=strlen(registro.email);

    for(int i = 0; i < tamanho; i++){
        char caracter = registro.email[i];
        if(caracter == '@'){
            return registro.email;
        }      
    }
    printf("Email invalido!\n");
    validar_email();
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
    retorno = fclose(dados_agenda); // Se o arquivo é fechado corretamente, então retorna 0
    if(retorno == 0 && vazio == 0){ 
        printf("Sem contatos armazenados!\n"); //<-- se arquivo existe e todos os contatos foram excluidos
    }
    limpar_buffer();
    printf("\nPressione qualquer tecla para finalizar.");
    getchar();   
}

void editar_contatos() {
    int id_contato;
    char dados[168];
    
    // Validação do Input
    do {
        printf("Digite 0 para voltar ao menu.\nID do registro: ");
        scanf("%i", &id_contato);
        
        if (id_contato == 0)             // Voltar para o menu
            return;
        else if (editar_aux(id_contato)) // Opção validada
            break;
        else {                           // Opção inválida
            system("cls");
            printf("ID invalido.\n");
        }
    } while (1);

    // Coleta os dados do arquivo
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return;
    }

    // Display dos dados pro usuário
    int id_aux = 1;
    while (fgets(dados, sizeof(dados), dados_agenda) != NULL) {
        if (id_aux == id_contato) {
            system("cls");
            printf("Dados: %s", dados);
            break;
        }
        id_aux++;
    }
    fclose(dados_agenda);

    // Novas informações
    printf ("Digite o nome: ");
    scanf("%s", registro.nome);
        
    validar_email();
        
    printf ("Digite o numero de celular: ");
    scanf("%s", registro.celular);
    
    dados_agenda = fopen("arquivo_agenda.txt", "r");
    temp_agenda  = fopen("temp_agenda.txt","w+");

    // Cria uma agenda temporária com o contato editado
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
        if (dados[0] == '\n')
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
