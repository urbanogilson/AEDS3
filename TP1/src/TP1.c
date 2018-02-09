#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP1.h"

//Função auxiliar do qsort()
int comparador(const void *a, const void *b)
{
	int comparacao = strcmp((*(struct Livro*)a).titulo, (*(struct Livro*)b).titulo);
	
	if (comparacao == 0)
	{
		return 0;
	}
	else
	{
		if (comparacao < 0)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}

//Salva arquivos na memória secundaria em modo binário
void salvaArquivo(char *endArquivo, Livro *livros, int tamanho)
{
	int i;
	FILE *arquivo = fopen(endArquivo, "wb");
	
	for (i = 0; i < tamanho; i++)
	{
		fwrite(&livros[i], sizeof(Livro), 1, arquivo);
	}
	
	fclose(arquivo);
	return;
}

//Particiona e Ordena M arquivos em memória primária
int ordena(char *endArquivo, Variaveis controle)
{
	//Livro livros[controle.M];
	Livro *livros = (Livro*) malloc(controle.M * sizeof(Livro));
	int contador = 0, total = 0;
	char temp[20];
	FILE *arquivo = fopen(endArquivo, "rb");

	fseek(arquivo, 0, SEEK_END);
	int tamarq1 = ftell(arquivo);
	tamarq1 /= sizeof(Livro);
	rewind(arquivo);

	while(tamarq1 > 0)
	{
		fread(&livros[total], sizeof(Livro), 1, arquivo);
		total++;
		if (total == controle.M)
		{
			contador++;
			sprintf(temp, "Temp%d", contador);
			qsort(livros, total, sizeof(Livro), comparador);
			salvaArquivo(temp, livros, total);
			total = 0;
		}
	tamarq1--;
	}

	if (total > 0)
	{
		contador++;
		sprintf(temp, "Temp%d", contador);
		qsort(livros, total, sizeof(Livro), comparador);
		salvaArquivo(temp, livros, total);
	}

	fclose(arquivo);
	free(livros);
	return contador;
}

//Etapa de merge, faz a intercação dos arquivos particionados pela função ordena()
void merge(char *endArquivo, char *entrada1, char* entrada2)
{
	Livro buffer1, buffer2;
	FILE *arq1 = fopen(entrada1, "rb");
	FILE *arq2 = fopen(entrada2, "rb");
	FILE *arquivo = fopen(endArquivo, "wb");

	fseek(arq1, 0, SEEK_END);
	fseek(arq2, 0, SEEK_END);

	int qtdArq1 = ftell(arq1);
	int qtdArq2 = ftell(arq2);
	qtdArq1 /= sizeof(Livro);
	qtdArq2 /= sizeof(Livro);
	rewind(arq1);
	rewind(arq2);

	int compara = 0;

	fread(&buffer1, sizeof(Livro), 1, arq1);
	fread(&buffer2, sizeof(Livro), 1, arq2);

	while(qtdArq1 > 0 && qtdArq2 > 0)
	{
		compara = strcmp(buffer1.titulo, buffer2.titulo);

		if (compara == 0)
		{
			fwrite(&buffer1, sizeof(Livro), 1, arquivo);
			fwrite(&buffer2, sizeof(Livro), 1, arquivo);
			fread(&buffer1, sizeof(Livro), 1, arq1);
			fread(&buffer2, sizeof(Livro), 1, arq2);
			qtdArq1--;
			qtdArq2--;
		}
		else if (compara < 0)
		{
			fwrite(&buffer1, sizeof(Livro), 1, arquivo);
			fread(&buffer1, sizeof(Livro), 1, arq1);
			qtdArq1--;
		}
		else if (compara > 0)
		{
			fwrite(&buffer2, sizeof(Livro), 1, arquivo);
			fread(&buffer2, sizeof(Livro), 1, arq2);
			qtdArq2--;
		}
	}

	while(qtdArq1 > 0)
	{
		fwrite(&buffer1, sizeof(Livro), 1, arquivo);
		fread(&buffer1, sizeof(Livro), 1, arq1);
		qtdArq1--;
	}

	while(qtdArq2 > 0)
	{
		fwrite(&buffer2, sizeof(Livro), 1, arquivo);
		fread(&buffer2, sizeof(Livro), 1, arq2);
		qtdArq2--;
	}

	fclose(arq1);
	fclose(arq2);
	fclose(arquivo);
}

//Função principal de ordenação externa, primeiro orderna M chaves e depois faz a união com a etapa de merge
void ordenacaoExterna(char *endArquivo, Variaveis controle)
{
	char temp1[20], temp2[20];
	int numArqs = ordena(endArquivo, controle);
	int i, flag = 0;

	char aux1[20] = {"saida"};
	char aux2[20] = {"saida1"};
	
	// Essa condição garante que o programa funcione independete se o número de arquivos temporários for par ou impar. 
	if (numArqs%2 == 1)
	{
		sprintf(aux1, "saida1");
		sprintf(aux2, "saida");
	}

	remove(endArquivo);

	for (i = 0; i < numArqs - 1; ++i)
	{
		sprintf(temp1, "Temp%d", i + 1);
		sprintf(temp2, "Temp%d", i + 2);
		if (i == 0)
		{
			merge(aux1, temp1, temp2);
			remove(temp1);
			remove(temp2);
		}
		else if (flag == 0)
		{
			merge(aux2, aux1, temp2);
			remove(aux1);
			remove(temp2);
			flag = 1;
		}
		else if (flag == 1)
		{
			merge(aux1, aux2, temp2);
			remove(aux2);
			remove(temp2);
			flag = 0;
		}
	}
}

//Coloca os livros ordenados em um arquivo "livros_ordenados" do tipo texto
void livros_ordenados(char *endArquivo)
{
	Livro buffer;
	FILE *arq = fopen(endArquivo, "rb");
	FILE *saida = fopen("livros_ordenados", "w");
	
	fseek(arq, 0, SEEK_END);

	int tam = ftell(arq);
	tam /= sizeof(Livro);
	rewind(arq);

	while(tam > 0)
	{
		fread(&buffer, sizeof(Livro), 1, arq);
		fprintf(saida, "%s %d\n", buffer.titulo, buffer.disponivel);
		tam--;
	}

	fclose(arq);
	fclose(saida);
}

// Separa os livros em E arquivos(estantes), e cria um arquivo índice com o primeiro e último livro de cada estante
void separa_livros(char *endArquivo, Variaveis controle)
{
	Livro livros;
	char estante[20];
	FILE *arquivo = fopen(endArquivo, "rb");
	FILE *saida[controle.E];
	FILE *indice = fopen("indice", "w");

	fseek(arquivo, 0, SEEK_END);
	int tam = ftell(arquivo);
	tam /= sizeof(Livro);
	rewind(arquivo);

	int i, j;
	for (i = 0; i < controle.E; i++)
	{
		sprintf(estante, "estante%d", i);
		saida[i] = fopen(estante, "wb");
		if (tam <= 0)
		{
			fprintf(indice, "#\n");
		}
		for (j = 0; j < controle.L && tam > 0; j++)
		{
			fread(&livros, sizeof(Livro), 1, arquivo);
			fwrite(&livros, sizeof(Livro), 1, saida[i]);
			tam--;
			controle.N--;
			if (j == 0)  
			{
				fprintf(indice, "%s ", livros.titulo);
			}
				else if (j == (controle.L - 1) || controle.N == 0)
			{
				fprintf(indice, "%s\n", livros.titulo);
			}
		}
	fclose(saida[i]);
	}

	fclose(indice);
	fclose(arquivo);
}

//Retorna o índice do arquivo em que se deve aplicar a busca binária
int buscaIndice(Livro *chave)
{
	int i = 0;
	Livro inicio, fim;
	
	FILE *indice = fopen("indice", "r");
	fscanf(indice, "%s", inicio.titulo);
	fscanf(indice, "%s", fim.titulo);
	
	while(!feof(indice) && strcmp(inicio.titulo, "#") != 0)
	{
		int comp1 = strcmp(inicio.titulo, chave->titulo);
		int comp2 = strcmp(fim.titulo, chave->titulo);
		if (comp1 <= 0 && comp2 >= 0)
		{
			fclose(indice);
			return i;
		}
	i++;
	fscanf(indice, "%s", inicio.titulo);
	fscanf(indice, "%s", fim.titulo);
	}

	fclose(indice);
	return -1;
}

int buscaBinaria(Livro *chave)
{
	int i = buscaIndice(chave);
	if (i < 0)
	{
		printf("livro nao encontrado\n");
		return 0;
	}
	
	char estanteN[10];
	sprintf(estanteN, "estante%d", i);
	FILE *estante = fopen(estanteN, "rb");

	fseek(estante, 0, SEEK_END);
	int tam = ftell(estante);
	tam /= sizeof(Livro);
	rewind(estante);

	int primeiro, meio, ultimo;
	primeiro = 0;
	ultimo = tam - 1;

	Livro aux;
	while(primeiro <= ultimo)
	{
		meio = (primeiro + ultimo)/2;
		fseek(estante, meio*sizeof(Livro), SEEK_SET);
		fread(&aux, sizeof(Livro), 1, estante);
		int comparacao = strcmp(chave->titulo, aux.titulo);

		if (comparacao == 0)
		{
			if (aux.disponivel == 0)
			{
				printf("emprestado\n");
				fclose(estante);
				return 1;
			}
			printf("disponivel na posicao %d na estante %d\n", meio, i);
			fclose(estante);
			return meio;
		}
		else if (comparacao < 1)
		{
			ultimo = meio - 1;
		}
		else
		{
			primeiro = meio + 1;
		}
	}

	printf("livro nao encontrado\n");
	fclose(estante);
	return 1;
}