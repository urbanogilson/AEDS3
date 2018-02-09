#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "TP0.h"
#define ALFABETO 26

int main(int argc, char const *argv[])
{
	Trie* raiz = cria_Trie();

    int num_dicionario = 0, num_texto = 0;

	/* pega o número de palavras do dicionário */
    scanf("%d", &num_dicionario);

    /* aloca espaço para as palavras do dicionário */
    char** entrada_dicionario = (char**) malloc(num_dicionario*sizeof(char*));
    
    int j;
    for (j = 0; j < num_dicionario; j++)
    {
    	entrada_dicionario[j]  = (char*) malloc(16*sizeof(char));
    }

	/* pega as palavras do dicionário */
    int i;
    for (i = 0; i < num_dicionario; i++)
    {
    	scanf("%s", entrada_dicionario[i]);
    	insere_Trie(raiz, entrada_dicionario[i]);
    }
    
    /* pega o número de palavras do texto */
    scanf("%d", &num_texto);

    /* aloca espaço para as palavras do texto */
    char** entrada_texto = (char**) malloc(num_texto*sizeof(char*));

    for (j = 0; j < num_texto; j++)
    {
    	entrada_texto[j]  = (char*) malloc(16*sizeof(char));
    }

    /* pega as palavras do texto e conta as orrencias das que estão no dicionario */
    /* Aproveitei esse loop para liberar a memória das palavras do texto */
    for (i = 0; i < num_texto; i++)
    {
    	scanf("%s", entrada_texto[i]);
    	busca_Trie(raiz, entrada_texto[i]);
    	free(entrada_texto[i]);
    }
    free(entrada_texto);

    /* Imprime as quantidade de ocorrências das palavras do dicionário */
    /* Aproveitei esse loop para liberar a memória das palavras do dicionário */
    for (i = 0; i < num_dicionario; i++)
    {
    	ocorrencias_Trie(raiz, entrada_dicionario[i]);
    	free(entrada_dicionario[i]);
    }
    free(entrada_dicionario);

    printf("\n");

    /* Chama a função e libera memória da árvore Trie */
   	libera_Trie(raiz);
    return 0;
}