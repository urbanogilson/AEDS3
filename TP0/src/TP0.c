#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "TP0.h"
#define ALFABETO 26

NO* cria_NO(char c)
{
	NO* no = (NO*) malloc(sizeof(NO));
	if (no == NULL)
	{
		return 0;
	}
	no->palavra = 0;
	no->letra = c;
	no->ocorrencias = 0;
	int i;
	for (i = 0; i < ALFABETO; i++)
	{
		no->Caracteres[i] = NULL;
	}
	return no;
}

Trie* cria_Trie()
{
	Trie* raiz = (Trie*) malloc(sizeof(Trie));
	if (raiz == NULL)
	{	
		printf("Erro na Alocacao\n");
		return 0;
	}
	(*raiz) = cria_NO(' ');
	return raiz;
}

/* Retorna um número de acordo a letra (casting)*/
int indice_Trie(char c)
{
	int indice = (int)c - 97;
	return indice;
}

/* Insere nós na árvore Trie */
int insere_Trie(Trie* raiz, char* texto)
{
	if (raiz == NULL)
	{
		return 0;
	}
	NO* atual = *raiz;
	int i = 0;
	int tamanho_texto = strlen(texto);

	while(atual->Caracteres[indice_Trie(texto[i])] != NULL && tamanho_texto > 0)
	{
		atual = atual->Caracteres[indice_Trie(texto[i])];
		if (tamanho_texto == 1)
		{
			atual->palavra = 1;
		}
		i++;
		tamanho_texto--;
	}

	while(tamanho_texto > 0)
	{
		NO* novo = cria_NO(texto[i]);
		atual->Caracteres[indice_Trie(texto[i])] = novo;
		atual = novo;
		if (tamanho_texto == 1)
		{
			atual->palavra = 1;	
		}
		i++;
		tamanho_texto--;
	}
	return 1;
}

/* Faz a busca da palavra do dicionário no texto e incrementa a ocorrencia da palavra */
int busca_Trie(Trie* raiz, char* texto)
{
	if (raiz == NULL)
	{
		return 0;
	}
	NO* atual = *raiz;
	int i = 0;
	int tamanho_texto = strlen(texto);

	while(atual->Caracteres[indice_Trie(texto[i])] != NULL && tamanho_texto > 0)
	{
		atual = atual->Caracteres[indice_Trie(texto[i])];
		if (tamanho_texto == 1 && atual->palavra == 1 && atual->letra == texto[i])
		{
			atual->ocorrencias++;
			return 1;
		}
		i++;
		tamanho_texto--;
	}
	return 0;
}

/* Imprime as ocorrências */
int ocorrencias_Trie(Trie* raiz, char* texto)
{
	if (raiz == NULL)
	{
		return 0;
	}
	NO* atual = *raiz;
	int i = 0;
	int tamanho_texto = strlen(texto);

	while(atual->Caracteres[indice_Trie(texto[i])] != NULL && tamanho_texto > 0)
	{
		atual = atual->Caracteres[indice_Trie(texto[i])];
		if (tamanho_texto == 1 && atual->palavra == 1 && atual->letra == texto[i])
		{
			printf("%d ", atual->ocorrencias);
			return 1;
		}
		i++;
		tamanho_texto--;
	}
	return 0;
}

/* Função recursiva que libera memória alocada dos nós */
void libera_No(NO* no)
{
	if (no == NULL)
	{
		return;
	}
	int i;
	for (i = 0; i < ALFABETO; ++i)
	{
		libera_No(no->Caracteres[i]);
	}
	free(no);
	no = NULL;
}

/* Função recursiva que libera memória de toda a árvore Trie*/
void libera_Trie(Trie* raiz)
{
	if (raiz == NULL)
	{
		return;
	}
	libera_No(*raiz);
	free(raiz);
}