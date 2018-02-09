#ifndef TP1
#define TP1

// N = Linhas
// M = Caracteres
// Dimensão do mapa da física (N x M)
// T = Quantidade de chaves
typedef struct Control
{
	int N, M, T;
}Control;

// Representação dos Vértices
typedef struct Vertex
{
	char caracter;
	int x, y; // Posição do vértice
	bool black_hole; // Vértice é buraco negro
	int X1, X2; // Coordenada que o buraco negro irá levar
	int n; // Número da aresta
}Vertex;

typedef struct Map
{
	Vertex **mapa; // Vértices
}Map;

typedef struct Graph
{
	int inicio, fim; // Inicio e Fim do Labirinto
	int **adjacency; // Lista e Adjacência
	int *degree;	// Grau de ligação de cada vertice
	int caminhos; // Quantidade de Caminhos possíveis
}Graph;

typedef struct Player
{
	char *key; // Mochila de Chaves
}Player;

void createMap(Map *maze, Control variables);
void freeMap(Map *maze, Control variables);
int cast(char caractere);
void getMap(Map *maze, Control variables);
void creatGraph(Graph *grafo, Control variables);
void creatPercursos(Graph *grafo, Control variables);
void insertEdge(Graph *grafo, int ini, int fim);
void freeGraph(Graph *grafo, Control variables);
int endBlackHole(Map *maze, Control variables, int x, int y);
void insert(Map *maze, Graph *grafo, Control variables);
void buscaLargura(Map *maze, Graph *grafo, Graph *aux, Control variables, int inicio, Graph *caminhos);
void buscaProfundidade(Graph *grafo, Control variables, int inicio, int *visitado, int contador, Graph *aux, int *linha, int *coluna);
void DFS(Map *maze, Graph *caminhos, Graph *grafo, Graph *aux, Control variables, int inicio);
void corrigeCaminhos(Map *maze, Graph *aux, Graph *grafo, Control variables, int coluna);
void VerificaCaminhos(Map *maze, Graph *aux, Graph *grafo, Player *one, Control variables);
int returnVertex(Map *maze, Control variables, int *x, int *y, int n);

#endif //TP1