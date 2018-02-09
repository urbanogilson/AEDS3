#ifndef TP3
#define TP3

// M = Linhas
// N = Colunas
typedef struct Control
{
	int M, N;
}Control;

typedef struct Grid
{
	int **matrix;
}Grid;

typedef struct Arg
{
	Control variables;
	Grid map;
	int line, sum;
}Arg;

void allocGrid(Grid *map, Control variables);
void freeGrid(Grid *map, Control variables);
void getGrid(Grid *map, Control variables);
void *sumLine(void *arg);
int max(int a, int b);

#endif //TP3