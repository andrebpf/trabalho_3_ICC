#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>

typedef struct cel{
	float val;
	int coluna;
	struct cel *proximo;
}celula;

typedef celula *ponteiro;

typedef struct{
	ponteiro *head;
	int num_lin;
	int num_col;
}matriz;

void criar_matriz(matriz *m)
{
    int lin, col;
	int i;

	system("cls");
        printf("MATRIZ ESPARSA - CRIAR (0 - SAIR)\n\n");
        printf("Digite o n�mero de linhas: ");
        scanf("%d",&lin);
        if(lin==0)
            exit(0);

        while(lin<0)
        {
            printf("N�mero inv�lido de linha! Digite novamente: ");
            scanf("%d", &lin);
        }

        printf("Digite o n�mero de colunas: ");
        scanf("%d",&col);
         if(lin==0)
            exit(0);

        while(col<0)
        {
            printf("N�mero inv�lido de coluna! Digite novamente: ");
            scanf("%d", &col);
        }

	m->num_lin = lin;
	m->num_col = col;
	m->head = (ponteiro*) malloc(lin*sizeof(ponteiro));
	for (i=0;i<lin;i++)
		m->head[i] = NULL;
}

void inserir_valor(matriz *m)
{
	int lin,col;
	float val;
	int op;

	do{
        fflush(stdin);
        printf("Digite n�mero da linha: ");
        scanf("%d",&lin);
        while(lin<0 || lin>=m->num_lin)
        {
            printf("N�mero inv�lido de linha! ");
            printf("\nInsira um n�mero entre 0 e %d: ",m->num_lin-1);
            scanf("%d",&lin);
        }
        printf("Digite o n�mero da coluna: ");
        scanf("%d",&col);
        while(col<0 || col>=m->num_col)
        {
            printf("N�mero inv�lido de coluna! ");
            printf("\nInsira um n�mero entre 0 e %d: ",m->num_col-1);
            scanf("%d",&col);
        }
        printf("Digite o valor: ");
        scanf("%f",&val);
        ponteiro anterior = NULL;
        ponteiro atual =  m->head[lin];

        while(atual != NULL && atual->coluna<col) /*procura uma c�lula em uma linha*/
        {
            anterior = atual; //o anterior passa a ser atual (0 vira 1)
            atual = atual->proximo; //o atual passa a ser proximo (1 vira 2)
        }

        if (atual != NULL && atual->coluna == col) //ele achou!! \o/
        {
            if(val==0) //ele vai zerar a celula e liberar mem�ria
            {
                if(anterior==NULL)
                    m->head[lin] = atual->proximo;
                else
                    anterior->proximo = atual->proximo;

                free(atual);
            }
            else //ele vai inserir um valor diferente de 0
                atual->val = val;
        }
        //o if anterior � pra quando a c�lula ou recebe atribui��o 0
        //ou quando um n�mero j� foi inserido nela anteriormente
        else if (val != 0) //esse aqui cria uma c�lula nova
        {
            ponteiro novo = (ponteiro) malloc(sizeof(celula));
            novo->coluna = col;
            novo->val = val;
            novo->proximo = atual;
            if(anterior==NULL)//ele vai ser o primeiro da linha
                m->head[lin] = novo; //a cabe�a da linha aponta pro novo
            else
                anterior->proximo = novo;
        }
        fflush(stdin);
        printf("\nDeseja cadastrar mais um valor? (1-sim / 0-n�o): ");
        scanf("%d",&op);
        while(op != 0 && op!= 1)
        {
            printf("\nOp��o inv�lida! (1-sim / 0-n�o): ");
            scanf("&d",&op);
        }
    }while(op!=0);
}

float consultar_valor (matriz *m)
{
	int lin;
	int col;

	printf("Digite n�mero da linha: ");
    scanf("%d",&lin);
	while(lin<0 || lin>=m->num_lin)
	{
		printf("N�mero inv�lido de linha!");
		printf("\nInsira um n�mero entre 0 e %d: ",m->num_lin-1);
		scanf("%d",&lin);
	}
	printf("Digite o n�mero da coluna: ");
    scanf("%d",&col);
	while(col<0 || col>=m->num_col)
	{
		printf("N�mero inv�lido de coluna!");
		printf("\nInsira um n�mero entre 0 e %d: ",m->num_col-1);
		scanf("%d",&col);
	}

	ponteiro atual = m->head[lin];

	while(atual != NULL && atual->coluna < col)//procurando a c�lula na linha
		atual = atual->proximo;

	if(atual !=NULL && atual->coluna == col)
		return atual->val;

	return 0;
}

float somar_linha(matriz *m)
{
	float soma=0.0;
	int lin;

	printf("Digite n�mero da linha: ");
    scanf("%d",&lin);
	while(lin<0 || lin>=m->num_lin)
	{
		printf("N�mero inv�lido de linha!");
		printf("\nInsira um n�mero entre 0 e %d: ",m->num_lin-1);
		scanf("%d",&lin);
	}

	ponteiro atual = m->head[lin];

	while(atual != NULL && atual->coluna < m->num_col)
	{
		soma+= atual->val;
		atual = atual->proximo;
	}
	return soma;
}

float somar_coluna(matriz *m)
{
	int i;
	int col;
	float soma=0.0;
	int flag =0;

	printf("Digite n�mero da coluna: ");
    scanf("%d",&col);
	while(col<0 || col>=m->num_col)
	{
		printf("N�mero inv�lido de coluna!");
		printf("\nInsira um n�mero entre 0 e %d: ",m->num_col-1);
		scanf("%d",&col);
	}

	ponteiro atual;

	for (i=0;i<m->num_lin;i++)
	{
	    if(m->head[i]!=NULL)
        {
            atual = m->head[i];
            while(atual != NULL && atual->coluna != col)
            {
                if(atual->proximo==NULL)
                    break;

                atual = atual->proximo;
            }
            if(atual->coluna == col)
                soma+=atual->val;
        }
	}

/*
	for (i=0;i<m->num_lin;i++)
	{
	    flag=0;
		if(m->head[i]!=NULL)
		{
			atual = m->head[i];
			while(atual != NULL && atual->coluna != col)
            {
                if(atual->proximo!=NULL)
                    atual = atual->proximo;
                else
                    flag=1;
            }
            if(flag==1)
                continue;

			soma+=atual->val;
		}
	}*/
	return soma;
}

void menu()
{

	matriz mat;
	int lin;
	int col;
	float val;
	float somalin=0.0;
	float somacol=0.0;

	int opcao = -1;

	do{
        criar_matriz(&mat);

        do{

            system("cls");
            printf("MATRIZ ESPARSA %d x %d\n\n",mat.num_lin, mat.num_col);
            printf("1 - Inserir valor em uma posi��o\n");
            printf("2 - Consultar valores de uma posi��o\n");
            printf("3 - Somar uma linha\n");
            printf("4 - Somar uma coluna\n");
            printf("5 - Excluir matriz\n");
            printf("0 - Sair\n\n");

            printf("Op��o escolhida: ");
            scanf("%d",&opcao);

            switch(opcao)
            {
                case 1:
                    system("cls");
                    printf("ATRIBUI��O DE VALOR\n\n");
                    inserir_valor(&mat);
                break;

                case 2:
                    system("cls");
                    printf("CONSULTAR VALOR\n\n");
                    val = consultar_valor(&mat);
                    printf("\nValor: %.2f\n",val);
                    system("pause");
                break;

                case 3:
                    system("cls");
                    printf("SOMAR LINHA\n\n");
                    somalin = somar_linha(&mat);
                    printf("Soma: %.2f\n",somalin);
                    system("pause");
                break;

                case 4:
                    system("cls");
                    printf("SOMAR COLUNA\n\n");
                    somacol = somar_coluna(&mat);

                    printf("Soma: %.2f\n",somacol);
                    system("pause");
                break;

                case 5:
                    free(mat.head);

                break;

                case 0:
                    free(mat.head);
                    exit(0);
            }
        }while(opcao!=5);
    }while(1);
}

int main()
{
	setlocale(LC_ALL,"Portuguese");
	menu();
	return 0;
}
