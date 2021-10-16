#include "TP0.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

No *NoCria(char c) {
  No *no = (No *)malloc(sizeof(No));

  if (no == NULL) {
    return NULL;
  }

  no->palavra = false;
  no->letra = c;
  no->ocorrencias = 0;

  for (size_t i = 0; i < ALFABETO; i++) {
    no->caracteres[i] = NULL;
  }

  return no;
}

Trie *TrieCria() {
  Trie *raiz = (Trie *)malloc(sizeof(Trie));

  if (raiz == NULL) {
    return NULL;
  }

  (*raiz) = NoCria(' ');

  return raiz;
}

/* Retorna um número de acordo a letra (casting)*/
int IndiceTrie(char c) { return (int)c - (int)'a'; }

/* Insere nós na árvore Trie */
int TrieInsere(Trie *raiz, char *texto) {
  if (raiz == NULL) {
    return 0;
  }

  No *atual = *raiz;
  size_t i = 0;
  size_t tamanho_texto = strlen(texto);

  while (atual->caracteres[IndiceTrie(texto[i])] != NULL && tamanho_texto > 0) {
    atual = atual->caracteres[IndiceTrie(texto[i])];

    if (tamanho_texto == 1) {
      atual->palavra = 1;
    }

    i++;
    tamanho_texto--;
  }

  while (tamanho_texto > 0) {
    No *novo = NoCria(texto[i]);

    atual->caracteres[IndiceTrie(texto[i])] = novo;

    atual = novo;
    if (tamanho_texto == 1) {
      atual->palavra = 1;
    }

    i++;
    tamanho_texto--;
  }

  return 1;
}

/* Faz a busca da palavra do dicionário no texto e incrementa a ocorrencia da
 * palavra */
int TrieBusca(Trie *raiz, char *texto) {
  if (raiz == NULL) {
    return 0;
  }

  No *atual = *raiz;
  size_t i = 0;
  size_t tamanho_texto = strlen(texto);

  while (atual->caracteres[IndiceTrie(texto[i])] != NULL && tamanho_texto > 0) {
    atual = atual->caracteres[IndiceTrie(texto[i])];

    if (tamanho_texto == 1 && atual->palavra == 1 && atual->letra == texto[i]) {
      atual->ocorrencias++;
      return 1;
    }

    i++;
    tamanho_texto--;
  }

  return 0;
}

/* Imprime as ocorrências */
int TrieOcorrencias(Trie *raiz, char *texto) {
  if (raiz == NULL) {
    return 0;
  }

  No *atual = *raiz;
  int i = 0;
  int tamanho_texto = strlen(texto);

  while (atual->caracteres[IndiceTrie(texto[i])] != NULL && tamanho_texto > 0) {
    atual = atual->caracteres[IndiceTrie(texto[i])];
    if (tamanho_texto == 1 && atual->palavra == 1 && atual->letra == texto[i]) {
      printf("%d ", atual->ocorrencias);
      return 1;
    }
    i++;
    tamanho_texto--;
  }
  return 0;
}

/* Função recursiva que libera memória alocada dos nós */
void NoLibera(No *no) {
  if (no == NULL) {
    return;
  }

  for (size_t i = 0; i < ALFABETO; ++i) {
    NoLibera(no->caracteres[i]);
  }

  free(no);
}

/* Função recursiva que libera memória de toda a árvore Trie*/
void TrieLibera(Trie *raiz) {
  if (raiz == NULL) {
    return;
  }

  NoLibera(*raiz);
  free(raiz);
}