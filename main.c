#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
------TO DO LIST------
- Determinante
**/



struct matriz{
	double data;
	int i;
	int j;
	struct matriz *prox;
};

struct info_matriz{
    int qtd_linhas;
	int qtd_colunas;
};

typedef struct info_matriz INFO_MATRIZ;
typedef INFO_MATRIZ *INFO_MATRIZ_PTR;

typedef struct matriz MATRIZ;
typedef MATRIZ *MATRIZ_PTR;

//-------------FUNÇÕES-----------------------//

int ReadInt(int *numero) {
	bool negativo = false;

	//Limpa o buffer inicial até encontrar um numero ou ate o buffer acabar
	char c = getchar();

	if (c == '\n' || c == '\0')
        c = getchar();

	while (c != '\n' && c != '\0' && (c < '0' || c > '9')) {
		//Se o usuario digitou o sinal de menos, salva para no final multiplar por -1
		if (c == '-')
			negativo = true;

		c = getchar();
	}

	//Se o buffer de entrada acabou, entao nao tem nenhum numero para ler
	if (c == '\n' || c == '\0')
		return 0;

	//Caso o usuario digitou algum digito, le os digitos ate acabar
	*numero = c - '0';
	c = getchar();
	while (c != '\n' && c != '\0' && c >= '0' && c <= '9') {
		*numero = (*numero) * 10 + c - '0';
		c = getchar();
	}

	//Certifica que o buffer continua limpo depois da leitura
	while (c != '\n' && c != '\0') {
		c = getchar();
	}

	//Se o usuario digitou um '-' antes de digitar o numero, deixa o numero negativo
	if (negativo)
		*numero *= -1;

	//retorna sucesso
	return 1;
}


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
	printf("\n\n            Pressione ENTER para voltar ao menu principal\n\n");
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
	int acao;

        int valid = ReadInt(&acao);
            while (!valid || acao<1 || acao>7){
                printf("Entrada invalida, tente novamente: ");
                valid = ReadInt(&acao);
            }

	return acao;
}


void atribuir_valor_pos(MATRIZ_PTR matriz, INFO_MATRIZ info_matriz){
    if (matriz == NULL){
        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }
    while (1){
        int i, j;
        double data;
        printf("Digite a linha da posicao: ");

        int valid = ReadInt(&i);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&i);
        }

        if (i > info_matriz.qtd_linhas || i<0){
            printf("Essa linha nao existe.\n");
            WaitENTER();
            return;
        }
        printf("Digite a coluna da posicao: ");

        valid = ReadInt(&j);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&j);
        }

        if (j > info_matriz.qtd_colunas || j<0){
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
        printf("Deseja adicionar mais valores?  1 - SIM     0 - NAO.\n");
        int acao;
        valid = ReadInt(&acao);
            while (!valid || acao<0 || acao>1){
                printf("Entrada invalida, tente novamente: ");
                valid = ReadInt(&acao);
            }

        Limpa_tela();
        if (acao == 0) return;
    }

}


//cria uma struct de matriz e coloca na Lista de matrizes
MATRIZ_PTR criar_matriz(INFO_MATRIZ_PTR info_matriz_ptr){
	Limpa_tela();
	int linhas, colunas;
	MATRIZ_PTR matriz = (MATRIZ_PTR)malloc(sizeof(MATRIZ));
	matriz->prox = NULL;
	do {
        printf("Digite a quantidade de linhas da matriz: ");
        int valid = ReadInt(&linhas);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&linhas);
        }

        if (linhas < 1){
            printf("Nao e possivel criar uma matriz com um numero nulo ou negativo de linhas.\n");
            printf("Tente novamente.\n");
        }
	} while (linhas < 1);

	do {
        printf("Digite a quantidade de colunas da matriz: ");

        int valid = ReadInt(&colunas);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&colunas);
        }

        if (colunas < 1){
            printf("Nao e possivel criar uma matriz com um numero nulo ou negativo de colunas.\n");
            printf("Tente novamente.\n");
        }
	} while (colunas < 1);

	info_matriz_ptr->qtd_colunas = colunas;
	info_matriz_ptr->qtd_linhas = linhas;
	printf("Matriz criada com sucesso!\n");
    printf("Deseja atribuir algum valor a uma posicao? 1 - SIM   0 - NAO\n");
    int acao;

    int valid = ReadInt(&acao);
            while (!valid || acao<0 || acao>1){
                printf("Entrada invalida, tente novamente: ");
                valid = ReadInt(&acao);
            }

    if (acao == 1) atribuir_valor_pos(matriz, *info_matriz_ptr);
    return matriz;
}

//
void consultar_valor_pos(MATRIZ_PTR matriz, INFO_MATRIZ info_matriz){
    if (matriz == NULL){

        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }
    int i, j;
    double data;
    printf("Digite o valor da linha que deseja consultar: ");

    int valid = ReadInt(&i);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&i);
        }

    if (i<0 || i>(info_matriz.qtd_linhas)){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", info_matriz.qtd_linhas, info_matriz.qtd_colunas);
        WaitENTER();
        return;
    }
    printf("Digite o valor da coluna que deseja consultar: ");

    valid = ReadInt(&j);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&j);
        }

    if (j<0 || j>(info_matriz.qtd_colunas)){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", info_matriz.qtd_linhas, info_matriz.qtd_colunas);
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

void consultar_soma_linha(MATRIZ_PTR matriz, INFO_MATRIZ info_matriz){
    if (matriz == NULL){
        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }

    int linha;
    double soma = 0;
    printf("Digite a linha que deseja consultar: ");

    int valid = ReadInt(&linha);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&linha);
        }

    if (linha<0 || linha>info_matriz.qtd_linhas){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", info_matriz.qtd_linhas, info_matriz.qtd_colunas);
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

void consultar_soma_coluna(MATRIZ_PTR matriz, INFO_MATRIZ info_matriz){
    if (matriz == NULL){
        printf("Essa matriz esta vazia.\n");
        WaitENTER();
        return;
    }

    int col;
    double soma = 0;
    printf("Digite a coluna que deseja consultar: ");

    int valid = ReadInt(&col);
        while (!valid){
            printf("Entrada invalida, tente novamente: ");
            valid = ReadInt(&col);
        }

    if (col<0 || col>info_matriz.qtd_colunas){
        printf("Valor invalido, a matriz possui %d linhas e %d colunas.\n", info_matriz.qtd_linhas, info_matriz.qtd_colunas);
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
MATRIZ_PTR matriz = NULL;
INFO_MATRIZ info_matriz;
splash_screen();
printf("\n\n\n                   Pressione ENTER para prosseguir.\n");
char c = getchar();
while (c != '\n') c = getchar();
Limpa_tela();
printf("                             AVISO!\n");
printf("\n\nO seu programa nao possui matrizes. Sera criada uma matriz inicial.\n\n");
printf("                    Pressione ENTER para prosseguir.\n");
	c = getchar();
	while (c != '\n') c = getchar();
matriz = criar_matriz(&info_matriz);
Limpa_tela();
int acao;
while(1){
acao = menu_principal();
    switch (acao) {
        case 1:
            matriz = criar_matriz(&info_matriz);
            break;

        case 2:
            consultar_valor_pos(matriz, info_matriz);
            break;

        case 3:
            consultar_soma_linha(matriz, info_matriz);
            break;

        case 4:
            consultar_soma_coluna(matriz, info_matriz);
            break;

        case 5:
            atribuir_valor_pos(matriz, info_matriz);
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
