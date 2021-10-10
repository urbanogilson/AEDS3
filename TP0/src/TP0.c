#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "TP0.h"

No *no_cria(char c)
{
	No *no = (No *)malloc(sizeof(No));

	if (no == NULL)
	{
		return NULL;
	}

	no->palavra = 0;
	no->letra = c;
	no->ocorrencias = 0;

	for (int i = 0; i < ALFABETO; i++)
	{
		no->caracteres[i] = NULL;
	}

	return no;
}

Trie *trie_cria()
{
	Trie *raiz = (Trie *)malloc(sizeof(Trie));

	if (raiz == NULL)
	{
		return NULL;
	}

	(*raiz) = no_cria(' ');

	return raiz;
}

/* Retorna um número de acordo a letra (casting)*/
int indice_Trie(char c)
{
	return (int)c - (int)'a';
}

/* Insere nós na árvore Trie */
int trie_insere(Trie *raiz, char *texto)
{
	if (raiz == NULL)
	{
		return 0;
	}

	No *atual = *raiz;
	int i = 0;
	int tamanho_texto = strlen(texto);

	while (atual->caracteres[indice_Trie(texto[i])] != NULL && tamanho_texto > 0)
	{
		atual = atual->caracteres[indice_Trie(texto[i])];

		if (tamanho_texto == 1)
		{
			atual->palavra = 1;
		}

		i++;
		tamanho_texto--;
	}

	while (tamanho_texto > 0)
	{
		No *novo = no_cria(texto[i]);

		atual->caracteres[indice_Trie(texto[i])] = novo;

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
int trie_busca(Trie *raiz, char *texto)
{
	if (raiz == NULL)
	{
		return 0;
	}

	No *atual = *raiz;
	int i = 0;
	int tamanho_texto = strlen(texto);

	while (atual->caracteres[indice_Trie(texto[i])] != NULL && tamanho_texto > 0)
	{
		atual = atual->caracteres[indice_Trie(texto[i])];

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
int trie_ocorrencias(Trie *raiz, char *texto)
{
	if (raiz == NULL)
	{
		return 0;
	}

	No *atual = *raiz;
	int i = 0;
	int tamanho_texto = strlen(texto);

	while (atual->caracteres[indice_Trie(texto[i])] != NULL && tamanho_texto > 0)
	{
		atual = atual->caracteres[indice_Trie(texto[i])];
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
void no_libera(No *no)
{
	if (no == NULL)
	{
		return;
	}

	for (int i = 0; i < ALFABETO; ++i)
	{
		no_libera(no->caracteres[i]);
	}

	free(no);
}

/* Função recursiva que libera memória de toda a árvore Trie*/
void trie_libera(Trie *raiz)
{
	if (raiz == NULL)
	{
		return;
	}

	no_libera(*raiz);
	free(raiz);
}