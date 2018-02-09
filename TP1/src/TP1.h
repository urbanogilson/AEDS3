#ifndef TP1
#define TP1

// Entradas
// N = Número de Livros da Biblioteca
// M = Número de Livros que pode estar em memória
// E = Número de Estantes
// L = Número de Livros suportados por cada estante
// K = Número de consultas a serem feitas pelos alunos

// Variáveis que controlam o programa
typedef struct Variaveis
{
	int N, M, E, L, K;
}Variaveis;

// Livros da Biblioteca
typedef struct Livro
{
	char titulo[51];
	int disponivel; 
}Livro;

int comparador(const void *a, const void *b);
void salvaArquivo(char *endArquivo, Livro *livros, int tamanho);
int ordena(char *endArquivo, Variaveis controle);
void merge(char *endArquivo, char *entrada1, char* entrada2);
void ordenacaoExterna(char *endArquivo, Variaveis controle);
void livros_ordenados(char *endArquivo);
void separa_livros(char *endArquivo, Variaveis controle);
int buscaIndice(Livro *chave);
int buscaBinaria(Livro *chave);

#endif // TP1