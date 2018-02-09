#ifndef TP0
#define TP0
#define ALFABETO 26

typedef struct NO
{
	bool palavra;
	char letra;
	int ocorrencias;
	struct NO* Caracteres[ALFABETO];
}NO;

typedef struct NO* Trie;

NO* cria_NO(char c);
Trie* cria_Trie();
int indice_Trie(char c);
int insere_Trie(Trie* raiz, char* texto);
int busca_Trie(Trie* raiz, char* texto);
int ocorrencias_Trie(Trie* raiz, char* texto);
void libera_No(NO* no);
void libera_Trie(Trie* raiz);

#endif // TP0
