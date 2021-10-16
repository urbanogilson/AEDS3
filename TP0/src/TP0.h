#ifndef TP0_TP0_H_
#define TP0_TP0_H_
#define ALFABETO 26
#include <stdbool.h>

typedef struct No {
  bool palavra;
  char letra;
  int ocorrencias;
  struct No *caracteres[ALFABETO];
} No;

typedef struct No *Trie;

No *NoCria(char c);
Trie *TrieCria();
int TrieInsere(Trie *raiz, char *texto);
int TrieBusca(Trie *raiz, char *texto);
int TrieOcorrencias(Trie *raiz, char *texto);
int TrieIndice(char c);
void NoLibera(No *no);
void TrieLibera(Trie *raiz);

#endif  // TP0_TP0_H_
