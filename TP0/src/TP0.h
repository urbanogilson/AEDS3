#ifndef TP0_H
#define TP0_H
#define ALFABETO 26

typedef struct No
{
	bool palavra;
	char letra;
	int ocorrencias;
	struct No *caracteres[ALFABETO];
} No;

typedef struct No *Trie;

No *no_cria(char c);
Trie *trie_cria();
int trie_insere(Trie *raiz, char *texto);
int trie_busca(Trie *raiz, char *texto);
int trie_ocorrencias(Trie *raiz, char *texto);
int trie_indice(char c);
void no_libera(No *no);
void trie_libera(Trie *raiz);

#endif // TP0_H
