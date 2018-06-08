#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

/**
------TO DO LIST------
- Criar uma struct que informa a qtd_linhas e qtd_colunas da matriz e tirá-la da struct
- Após isso modificar as funções passando essa nova struct como parâmetro
- Colocar as funções para receber somente números e impedir o usuario de colocar letras ou numeros inválidos
**/


//i: linha, j: coluna

void splash_screen(){
    printf("        .___  ___.      ___   .___________..______       __   ________ \n");
    printf("        |   \\/   |     /   \\  |           ||   _  \\     |  | |       / \n");
    printf("        |  \\  /  |    /  ^  \\ `---|  |----`|  |_)  |    |  | `---/  /  \n");
    printf("        |  |\\/|  |   /  /_\\  \\    |  |     |      /     |  |    /  /   \n");
    printf("        |  |  |  |  /  _____  \\   |  |     |  |\\  \\----.|  |   /  /----. \n");
    printf("        |__|  |__| /__/     \\__\\  |__|     | _| `._____||__|  /________| \n");
    printf("\n");
    printf(" _______     _______..______      ___      .______          _______.     ___ \n");
    printf("|   ____|   /       ||   _  \\    /   \\     |   _  \\        /       |    /   \\ \n");
    printf("|  |__     |   (----`|  |_)  |  /  ^  \\    |  |_)  |      |   (----`   /  ^  \\ \n");
    printf("|   __|     \\   \\    |   ___/  /  /_\\  \\   |      /        \\   \\      /  /_\\  \\ \n");
    printf("|  |____.----)   |   |  |     /  _____  \\  |  |\\  \\----.----)   |    /  _____  \\ \n");
    printf("|_______|_______/    | _|    /__/     \\__\\ | _| `._____|_______/    /__/     \\__\\ \n");
}

struct matriz{
	double data;
	int qtd_linhas;
	int qtd_colunas;
	int i;
	int j;
	struct matriz *prox;
};

typedef struct matriz MATRIZ;
typedef MATRIZ *MATRIZ_PTR;

//-------------FUNÇÕES-----------------------//

char Input(int min, int max){
    char c;
    while ((c = getchar()) == '\n');
    while (c < min || c > max){
        printf("Valor invalido. Tente novamente: ");
        while ((c = getchar() == '\n'));
    }
    return c;
}

void WaitENTER() {
	printf("\n\n        Pressione ENTER para voltar ao menu principal\n\n");
	char c = getchar();
	while (c != '\n') c = getchar();
}


void Limpa_tela(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return;
}

int menu_principal(){
	Limpa_tela();
	printf("                             Matriz Esparsa\n");
	printf("\n\n\n\n\n");
	printf("1 - Criar matriz                              2 - Consultar valor de uma posicao\n");
	printf("3 - Consultar valor soma de linha             4 - Consultar valor de soma de coluna\n");
	printf("5 - Atribuir valor a uma posicao              6 - Sobre\n");
	printf("7 - Sair\n\n\n\n\n\n");
	printf("Digite a opcao desejada: ");
	char acao;
	acao = Input('1', '7') - '0';
	fflush(stdin);
	return acao;
}


void atribuir_valor_pos(MATRIZ_PTR matriz){
    if (matriz == NULL){
        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }
    while (1){
        int i, j;
        double data;
        printf("Digite a linha da posicao: ");
        scanf("%d", &i);
        fflush(stdin);
        //printf("qtd_linhas  = %d e qtd_colunas = %d\n", matriz->qtd_linhas, matriz->qtd_colunas);
        if (i > matriz->qtd_linhas || i<0){
            printf("Essa linha nao existe.\n");
            WaitENTER();
            return;
        }
        printf("Digite a coluna da posicao: ");
        scanf("%d", &j);
        fflush(stdin);
        if (j > matriz->qtd_colunas || j<0){
            printf("Essa coluna nao existe.\n");
            WaitENTER();
            return;
        }

        printf("Digite o valor que deseja atribuir a posicao: ");
        scanf("%lf", &data);
        fflush(stdin);


        //verifica se a posicao ja esta sendo usada
        MATRIZ_PTR primeira_pos_matriz = matriz; //armazena a primeira posicao da lista
        while (matriz->prox != NULL){
            if ((matriz->i == i) && (matriz->j == j)){
                matriz->data = data;
                return;
            }
            matriz = matriz->prox;
        }
        matriz = primeira_pos_matriz;


        MATRIZ_PTR nova_pos = (MATRIZ_PTR)malloc(sizeof(MATRIZ));
        nova_pos->prox = NULL;

        //percorre a lista ate chegar na ultima posicao
        while(matriz->prox != NULL){
          matriz = matriz->prox;
        }
        matriz->prox = nova_pos;
        nova_pos->data = data;
        nova_pos->i = i;
        nova_pos->j = j;
        nova_pos->qtd_colunas = matriz->qtd_colunas;
        nova_pos->qtd_linhas = matriz->qtd_linhas;
        printf("Deseja adicionar mais valores?  1 - SIM     0 - NAO.\n");
        char input;
        //scanf("%d", &input);
        input = Input('0', '1') - '0';
        fflush(stdin);
        Limpa_tela();
        if (input == 0) return;
    }

}

//cria uma struct de matriz e coloca na Lista de matrizes
MATRIZ_PTR criar_matriz(){
	Limpa_tela();
	int linhas, colunas;
	MATRIZ_PTR matriz = (MATRIZ_PTR)malloc(sizeof(MATRIZ));
	matriz->prox = NULL;
	do {
        printf("Digite a quantidade de linhas da matriz: ");
        scanf("%d", &linhas);
        fflush(stdin);
        if (linhas < 1){
            printf("Nao e possivel criar uma matriz com um numero nulo ou negativo de linhas.\n");
            printf("Tente novamente.\n");
        }
	} while (linhas < 1);

	do {
        printf("Digite a quantidade de colunas da matriz: ");
        scanf("%d", &colunas);
        fflush(stdin);
        if (colunas < 1){
            printf("Nao e possivel criar uma matriz com um numero nulo ou negativo de colunas.\n");
            printf("Tente novamente.\n");
        }
	} while (colunas < 1);

	matriz->qtd_colunas = colunas;
	matriz->qtd_linhas = linhas;
	printf("Matriz criada com sucesso!\n");
    printf("Deseja atribuir algum valor a uma posicao? 1 - SIM   0 - NAO\n");
    int num;
    scanf("%d", &num);
    fflush(stdin);
    if (num == 1) atribuir_valor_pos(matriz);
    return matriz;
}

//
void consultar_valor_pos(MATRIZ_PTR matriz){
    if (matriz == NULL){

        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }
    int i, j;
    double data;
    printf("Digite o valor da linha que deseja consultar: ");
    scanf("%d", &i);
    fflush(stdin);
    if (i<0 || i>matriz->qtd_linhas){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", matriz->qtd_linhas, matriz->qtd_colunas);
        WaitENTER();
        return;
    }
    printf("Digite o valor da coluna que deseja consultar: ");
    scanf("%d", &j);
    fflush(stdin);
    if (j<0 || j>matriz->qtd_colunas){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", matriz->qtd_linhas, matriz->qtd_colunas);
        WaitENTER();
        return;
    }
    //busca o valor na matriz
    while (matriz != NULL){
        if ((matriz->i == i) && (matriz->j == j)){
            data = matriz->data;
            printf("O valor da posicao (%d,%d) e: %lf\n", i, j, data);
            WaitENTER();
            return;
        }
        matriz = matriz->prox;
    }
    printf("O valor da posicao (%d,%d) e: 0\n", i, j);
    WaitENTER();
    return;
}

void consultar_soma_linha(MATRIZ_PTR matriz){
    if (matriz == NULL){
        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }

    int linha;
    double soma = 0;
    printf("Digite a linha que deseja consultar: ");
    scanf("%d", &linha);
    fflush(stdin);
    if (linha<0 || linha>matriz->qtd_linhas){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", matriz->qtd_linhas, matriz->qtd_colunas);
        WaitENTER();
        return;
    }
    while(matriz != NULL){
        if (matriz->i == linha)
                soma += matriz->data;
        matriz = matriz->prox;
    }
    printf("A soma da linha %d e: %lf\n", linha, soma);
    WaitENTER();
    return;
}

void consultar_soma_coluna(MATRIZ_PTR matriz){
    if (matriz == NULL){
        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }

    int col;
    double soma = 0;
    printf("Digite a coluna que deseja consultar: ");
    scanf("%d", &col);
    fflush(stdin);
    if (col<0 || col>matriz->qtd_colunas){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", matriz->qtd_linhas, matriz->qtd_colunas);
        WaitENTER();
        return;
    }
    while(matriz != NULL){
        if (matriz->j == col)
                soma += matriz->data;
        matriz = matriz->prox;
    }
    printf("A soma da coluna %d e: %lf\n", col, soma);
    WaitENTER();
    return;
}

//Informa ao usuario a descricao do programa e criadores
void MenuSobre() {
	Limpa_tela();
	printf("                    Gerenciador de notas\n");
	printf("                       Sobre o projeto       \n\n\n\n\n\n");
	printf("        Programa para gerenciamento de matrizes esparsas\n\n");
	printf("             As posicões vazias sao tomadas como contendo o valor 0\n\n");
	printf(" Projeto da disciplina de Introducao a Ciencia da Computacao I\n\n");
	printf("                 Universidade de Sao Paulo\n\n\n");
	printf("\n\n   Pressione ENTER para seguir para as informacões dos autores\n\n");
	char c = getchar();
	while (c != '\n') c = getchar();

	Limpa_tela();
	printf("                         Criado por:\n");
	printf("                       Vinicius Ribeiro\n");
	printf("                       vinicius.r@usp.br\n");
	printf("                 github.com/vinicius-r-silva\n\n");
	printf("                             e\n\n");
	printf("                  Gabriel Santos Nicolau:\n");
	printf("                gabriel.nicolau97@hotmail.com\n");
	printf("                     github.com/7Nic\n\n");
	WaitENTER();
}


//--------------------MAIN--------------------//
int main (){
//setlocale(LC_ALL, "Portuguese");
MATRIZ_PTR matriz = NULL;
splash_screen();
printf("\n\n\n                   Pressione ENTER para prosseguir.\n");
char c = getchar();
while (c != '\n') c = getchar();
Limpa_tela();
printf("                             AVISO!\n");
printf("\n\nO seu programa nao possui matrizes. Sera criada uma matriz inicial.\n\n");
printf("               Pressione ENTER para prosseguir.\n");
	c = getchar();
	while (c != '\n') c = getchar();
matriz = criar_matriz();
Limpa_tela();
int acao;
while(1){
acao = menu_principal();
    switch (acao) {
        case 1:
            matriz = criar_matriz();
            break;

        case 2:
            consultar_valor_pos(matriz);
            break;

        case 3:
            consultar_soma_linha(matriz);
            break;

        case 4:
            consultar_soma_coluna(matriz);
            break;

        case 5:
            atribuir_valor_pos(matriz);
            break;

        case 6:
            MenuSobre();
            break;

        case 7:
            return 0;
            break;

        default:
            printf("Valor invalido.\n");
            WaitENTER();
    }

}
}
