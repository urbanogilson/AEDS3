#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "TP0.h"

int main(void)
{
    Trie *raiz = trie_cria();

    int num_dicionario = 0, num_texto = 0;

    /* pega o número de palavras do dicionário */
    scanf("%d", &num_dicionario);

    /* aloca espaço para as palavras do dicionário */
    char **entrada_dicionario = (char **)malloc(num_dicionario * sizeof(char *));

    for (int j = 0; j < num_dicionario; j++)
    {
        entrada_dicionario[j] = (char *)malloc(16 * sizeof(char));
    }

    /* pega as palavras do dicionário */
    for (int i = 0; i < num_dicionario; i++)
    {
        scanf("%s", entrada_dicionario[i]);
        trie_insere(raiz, entrada_dicionario[i]);
    }

    /* pega o número de palavras do texto */
    scanf("%d", &num_texto);

    /* aloca espaço para as palavras do texto */
    char **entrada_texto = (char **)malloc(num_texto * sizeof(char *));

    for (int j = 0; j < num_texto; j++)
    {
        entrada_texto[j] = (char *)malloc(16 * sizeof(char));
    }

    /* pega as palavras do texto e conta as orrencias das que estão no dicionario */
    /* Aproveitei esse loop para liberar a memória das palavras do texto */
    for (int i = 0; i < num_texto; i++)
    {
        scanf("%s", entrada_texto[i]);
        trie_busca(raiz, entrada_texto[i]);
        free(entrada_texto[i]);
    }
    free(entrada_texto);

    /* Imprime as quantidade de ocorrências das palavras do dicionário */
    /* Aproveitei esse loop para liberar a memória das palavras do dicionário */
    for (int i = 0; i < num_dicionario; i++)
    {
        trie_ocorrencias(raiz, entrada_dicionario[i]);
        free(entrada_dicionario[i]);
    }
    free(entrada_dicionario);

    printf("\n");

    /* Chama a função e libera memória da árvore Trie */
    trie_libera(raiz);
    return 0;
}