#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP1.h"

int main()
{
	int i;
	Variaveis controle;
	Livro livros;
	
	//Faz a leitura das váriveis de controle
	scanf("%d %d %d %d %d", &controle.N, &controle.M, &controle.E, &controle.L, &controle.K);

	FILE *arq = fopen("saida", "wb");

	//Faz a leitura dos livros da biblioteca pela entrada padão e coloca em um arquivo, fazendo escrita binária
	for (i = 0; i < controle.N; i++)
	{
		scanf("%s %d", livros.titulo, &livros.disponivel);
		fwrite(&livros, sizeof(Livro), 1, arq);
	}
	fclose(arq);

	ordenacaoExterna("saida", controle);
	livros_ordenados("saida");
	separa_livros("saida", controle);

	Livro busca;

	// Efetua a busca dos livros
	for (i = 0; i < controle.K; i++)
	{
		scanf("%s", busca.titulo);
		buscaBinaria(&busca);
	}

	//Remove o arquivo auxiliar que foi utilizado durante a execução do programaa
	remove("saida");

	return 0;
}