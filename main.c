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
    printf("\nInforme a operação desejada: \n1) Incluir um novo contato; \n2) Excluir um contato existente; \n3) Alterar um contato existente; \n4) Listar todos os contatos cadastrados; \n5) Localizar um contato.\n");
    scanf("%d",&itemMenu);
    
    
	switch (itemMenu){
		case 1: {   
            incluir_dados();     
        } break;
        case 2: {
            excluir_contato();
        } break;    
        case 3: {
                   
        } break;
        case 4: {
            listar_contatos();   
        } break;
        case 5: {
               
        } break;
		default: {
            printf("Opcao Errada!\n");  
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
        scanf("%[^\n]%*c", registro.nome);
        
        validar_email();
        
        printf ("Digite o numero de celular: ");
        scanf("%[^\n]%*c", registro.celular);

        fprintf(dados_agenda, "%d, %s, %s, %s\n", registro.cod, registro.nome, registro.email, registro.celular); //Essa parte registra no arquivo
    }
    fclose(dados_agenda);

    printf("Contato Salvo!");
    printf("\nPressione qualquer tecla para finalizar.");
    getchar();
}

void excluir_contato(void){
	int id_contato; 
	char conteudo[200]; 
	int linha = 1;
	int aux_excluido=0;
	printf("Informe o ID do contato para deletar: \n");
	scanf("%d",&id_contato);
	limpar_buffer();
	
	dados_agenda = fopen("arquivo_agenda.txt","r+");
	temp_agenda  = fopen("temp_agenda.txt","w+");
	
	if (dados_agenda == NULL) {
        printf("Erro na abertura do arquivo.\n");
    } else {
        printf("Arquivo aberto.\n");
		while(fgets (conteudo, 200, dados_agenda)) {
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
		printf("Contato Excluído!");	
	}else{
		printf("Erro ao excluir: contato não encontrado!\n");
	}
    printf("\nPressione qualquer tecla para finalizar.\n");
    getchar();
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
    scanf("%[^\n]%*c", registro.email);

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
        }    
    }
    retorno = fclose(dados_agenda);   
    if(retorno == 0){
        limpar_buffer();
        printf("\nPressione qualquer tecla para finalizar.");
        getchar();
    }else {
        printf("Erro ao fechar arquivo!");
    }    
}


int main() {
	setlocale(LC_ALL, "");
	menuPrincipal(0);
	return 0;
}