#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TP0.h"

int main(void) {
  Trie *raiz = TrieCria();

  size_t num_dicionario = 0, num_texto = 0;

  /* pega o número de palavras do dicionário */
  scanf("%zu", &num_dicionario);

  /* aloca espaço para as palavras do dicionário */
  char **entrada_dicionario = (char **)malloc(num_dicionario * sizeof(char *));

  for (size_t j = 0; j < num_dicionario; j++) {
    entrada_dicionario[j] = (char *)malloc(16 * sizeof(char));
  }

  /* pega as palavras do dicionário */
  for (size_t i = 0; i < num_dicionario; i++) {
    scanf("%s", entrada_dicionario[i]);
    TrieInsere(raiz, entrada_dicionario[i]);
  }

  /* pega o número de palavras do texto */
  scanf("%zu", &num_texto);

  /* aloca espaço para as palavras do texto */
  char **entrada_texto = (char **)malloc(num_texto * sizeof(char *));

  for (size_t j = 0; j < num_texto; j++) {
    entrada_texto[j] = (char *)malloc(16 * sizeof(char));
  }

  /* pega as palavras do texto e conta as orrencias das que estão no dicionario
   */
  /* Aproveitei esse loop para liberar a memória das palavras do texto */
  for (size_t i = 0; i < num_texto; i++) {
    scanf("%s", entrada_texto[i]);
    TrieBusca(raiz, entrada_texto[i]);
    free(entrada_texto[i]);
  }
  free(entrada_texto);

  /* Imprime as quantidade de ocorrências das palavras do dicionário */
  /* Aproveitei esse loop para liberar a memória das palavras do dicionário */
  for (size_t i = 0; i < num_dicionario; i++) {
    TrieOcorrencias(raiz, entrada_dicionario[i]);
    free(entrada_dicionario[i]);
  }
  free(entrada_dicionario);

  printf("\n");

  /* Chama a função e libera memória da árvore Trie */
  TrieLibera(raiz);
  return 0;
}