#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TP2.h"

void createMap(Map *maze, Control variables)
{
	int i, j;
	maze->mapa = (Vertex**) malloc(variables.N * sizeof(Vertex*));
	for (i = 0; i < variables.N; i++)
	{
		maze->mapa[i] = (Vertex*) malloc(variables.M * sizeof(Vertex));
		for (j = 0; j < variables.M; j++)
		{
			maze->mapa[i][j].caracter = '0';
			maze->mapa[i][j].x = 0;
			maze->mapa[i][j].y = 0;
			maze->mapa[i][j].black_hole = 0;
			maze->mapa[i][j].X1 = 0;
			maze->mapa[i][j].X2 = 0;
			maze->mapa[i][j].n = 0;
		}
	}
}

void freeMap(Map *maze, Control variables)
{
	int i;
	for (i = 0; i < variables.N; i++)
	{
		free(maze->mapa[i]);
	}
	free(maze->mapa);
}

int cast(char caractere)
{
	int inteiro = (int)caractere - '0';
	return inteiro;
}

void getMap(Map *maze, Control variables)
{
	int i, j;
	char position, x2;
	int X = variables.N - 1, Y;
	int numVertices = 0;
	for (i = 0; i < variables.N; i++)
	{
		Y = 0;
		for (j = 0; j < variables.M; j++)
		{
			scanf("%c", &position);
			if (cast(position) >= 0 && cast(position) <= 9)
			{
				maze->mapa[i][j].caracter = 'B';
				
				scanf("%c", &x2);
				maze->mapa[i][j].black_hole = 1;
				maze->mapa[i][j].X1 = cast(position);
				maze->mapa[i][j].X2 = cast(x2);

				maze->mapa[i][j].x = X;
				maze->mapa[i][j].y = Y;
				Y++;

				maze->mapa[i][j].n = numVertices;
				numVertices++;
			}
			else if (position != ' ' && position != '\n')
			{
				maze->mapa[i][j].caracter = position;

				maze->mapa[i][j].x = X;
				maze->mapa[i][j].y = Y;
				Y++;

				maze->mapa[i][j].n = numVertices;
				numVertices++;
			}
			else
			{
				j--;
			}
		}
		X--;
	}
}

void creatGraph(Graph *grafo, Control variables)
{
	int i, j;
	grafo->adjacency = (int**) malloc((variables.N * variables.M) * sizeof(int*));
	for (i = 0; i < (variables.N * variables.M); i++)
	{
		grafo->adjacency[i] = (int*) malloc(4 * sizeof(int));
		for (j = 0; j < 4; j++)
		{
			grafo->adjacency[i][j] = 0;
		}
	}
	grafo->caminhos = 0;
	grafo->degree = (int*) calloc((variables.N * variables.M), sizeof(int));
}

void creatPercursos(Graph *grafo, Control variables)
{
	int i, j;
	grafo->adjacency = (int**) malloc((variables.N * variables.M) * sizeof(int*));
	for (i = 0; i < (variables.N * variables.M); i++)
	{
		grafo->adjacency[i] = (int*) malloc((variables.N * variables.M) * sizeof(int));
		for (j = 0; j < (variables.N * variables.M); j++)
		{
			grafo->adjacency[i][j] = 0;
		}
	}
	grafo->degree = (int*) calloc((variables.N * variables.M), sizeof(int));
}

void insertEdge(Graph *grafo, int ini, int fim)
{
	grafo->adjacency[ini][grafo->degree[ini]] = fim;
	grafo->degree[ini]++; 
}

void freeGraph(Graph *grafo, Control variables)
{
	int i;
	for (i = 0; i < (variables.N * variables.M); i++)
	{
		free(grafo->adjacency[i]);
	}
	free(grafo->adjacency);
	free(grafo->degree);
}

int endBlackHole(Map *maze, Control variables, int x, int y)
{
	int i, j;
	for (i = 0; i < variables.N; i++)
	{
		for (j = 0; j < variables.M; j++)
		{
			if (maze->mapa[i][j].x == x && maze->mapa[i][j].y == y)
			{
				return maze->mapa[i][j].n;
			}
		}
	}
	return -1;
}

void insert(Map *maze, Graph *grafo, Control variables)
{
	int i, j;
	for (i = 0; i < variables.N; i++)
	{
		for (j = 0; j < variables.M; j++)
		{
			if (maze->mapa[i][j].caracter == 'V')
			{
				grafo->inicio = maze->mapa[i][j].n;
			}
			else if (maze->mapa[i][j].caracter == 'E')
			{
				grafo->fim = maze->mapa[i][j].n;
			}
			if (maze->mapa[i][j].black_hole == 1)
			{
				//insertEdge(grafo, maze->mapa[i][j].n, endBlackHole(maze, variables, maze->mapa[i][j].X1, maze->mapa[i][j].X2));
			}
			else
			{
				if (i - 1 >= 0) // cima
				{
					if (maze->mapa[i - 1][j].caracter != '#' && maze->mapa[i][j].caracter != '#')
					{
						insertEdge(grafo, maze->mapa[i][j].n, maze->mapa[i - 1][j].n);
					}
				}
				if (j - 1 >= 0) // esquerda
				{
					if (maze->mapa[i][j - 1].caracter != '#' && maze->mapa[i][j].caracter != '#')
					{
						insertEdge(grafo, maze->mapa[i][j].n, maze->mapa[i][j - 1].n);
					}
				}
				if (j + 1 < variables.M) // direita
				{	
					if (maze->mapa[i][j + 1].caracter != '#' && maze->mapa[i][j].caracter != '#')
					{
						insertEdge(grafo, maze->mapa[i][j].n, maze->mapa[i][j + 1].n);
					}
				}
				if (i + 1 < variables.N) // baixo
				{	
					if (maze->mapa[i + 1][j].caracter != '#' && maze->mapa[i][j].caracter != '#')
					{
						insertEdge(grafo, maze->mapa[i][j].n, maze->mapa[i + 1][j].n);
					}
				}
			}
		}
	}
}

void buscaLargura(Map *maze, Graph *grafo, Graph *aux, Control variables, int inicio, Graph *caminhos)
{
	int i, *fila, IF = 0, FF = 0, contador = 1, vert;
	int visitado[variables.N*variables.M];

	for (i = 0; i < (variables.N * variables.M); i++)
	{
		visitado[i] = 0;
	}
	fila = (int*) malloc((variables.N * variables.M) * sizeof(int));
	FF++;
	fila[FF] = inicio;
	visitado[inicio] = contador;
	
	while(IF != FF)
	{
		IF = (IF + 1) % (variables.N * variables.M);
		vert = fila[IF];
		contador++;
		for (i = 0; i < grafo->degree[vert]; i++)
		{
			if (!visitado[grafo->adjacency[vert][i]] && vert != grafo->fim)
			{			
				FF = (FF + 1) % (variables.N * variables.M);
				fila[FF] = grafo->adjacency[vert][i];
				visitado[grafo->adjacency[vert][i]] = contador;

				caminhos->adjacency[vert][caminhos->degree[vert]] = fila[FF];
				caminhos->degree[vert]++;

			}
		}
	}

	caminhos->inicio = grafo->inicio;
	caminhos->fim = grafo->fim;

	DFS(maze, caminhos, grafo, aux, variables, grafo->inicio);

	free(fila);
}

void buscaProfundidade(Graph *grafo, Control variables, int inicio, int *visitado, int contador, Graph *aux, int *linha, int *coluna)
{
	int i, j;

	visitado[inicio] = contador;
	for (i = 0; i < grafo->degree[inicio]; i++)
	{
		if (!visitado[grafo->adjacency[inicio][i]])
		{
			if (i > 0)
			{
				for (j = 0; j < (variables.N * variables.M); j++)
				{
					if (aux->adjacency[j][*coluna] == inicio)
					{
						(*linha) = j + 1;
						(*coluna)++;
						
						while(j > 0)
						{
							aux->adjacency[j][*coluna] = aux->adjacency[j][(*coluna) - 1];
							j--;
						}
						aux->adjacency[0][*coluna] = grafo->inicio;
						break;
					}
				}
			}
			aux->adjacency[*linha][*coluna] = grafo->adjacency[inicio][i];
			(*linha)++;

			buscaProfundidade(grafo, variables, grafo->adjacency[inicio][i], visitado, contador + 1, aux, linha, coluna);
		}
	}
}

void DFS(Map *maze, Graph *caminhos, Graph *grafo, Graph *aux, Control variables, int inicio)
{
	int i, contador = 0;

	int visitado[(variables.N * variables.M)];

	for (i = 0; i < (variables.N * variables.M); i++)
	{
		visitado[i] = 0;
	}
	
	aux->inicio = caminhos->inicio;
	aux->fim = caminhos->fim;

	int linha = 0, coluna = 0;
	aux->adjacency[0][0] = caminhos->inicio;
	linha++;

	buscaProfundidade(caminhos, variables, inicio, visitado, contador, aux, &linha, &coluna);

	corrigeCaminhos(maze, aux, grafo, variables, coluna);

	aux->caminhos = coluna;
}

void corrigeCaminhos(Map *maze, Graph *aux, Graph *grafo, Control variables, int coluna)
{
	int i, j, k, l;

	for (i = 0; i <= coluna; i++)
	{
		for (j = 0; j < (variables.N * variables.M); j++)
		{
			if (aux->adjacency[j][i] == aux->fim)
			{
				break;
			}
			if (aux->adjacency[j][i] == 0 && aux->adjacency[j + 1][i] == 0)
			{
				for (k = 0; k < variables.N; k++)
				{
					for (l = 0; l < variables.M; l++)
					{
						if (j > 1 && maze->mapa[k][l].n == aux->adjacency[j - 1][i])
						{
							if (maze->mapa[k][l].black_hole == 1)
							{
								aux->adjacency[j][i] = endBlackHole(maze, variables, maze->mapa[k][l].X1, maze->mapa[k][l].X2);
							}
						}
					}
				}
			}
			if (aux->adjacency[j][i] == 0 && aux->adjacency[j + 1][i] == 0 && j > 1 && aux->adjacency[j - 1][i] != aux->fim)
			{
				for (l = 0; l < grafo->degree[aux->adjacency[j - 1][i]]; l++)
				{
					if (grafo->adjacency[aux->adjacency[j - 1][i]][l] == aux->fim)
					{
						aux->adjacency[j][i] = aux->fim;
					}
				}
				break;
			}
		}
	}
}

void VerificaCaminhos(Map *maze, Graph *aux, Graph *grafo, Player *one, Control variables)
{
	int i, j, k;
	int x, y;
	int qKeys = 0;
	int dist[aux->caminhos], distancia;
	bool tem_chave = 0;

	one->key = (char*) malloc((variables.T + 1) * sizeof(char));

	for (i = 0; i <= aux->caminhos; i++)
	{
		dist[i] = 1;
		qKeys = 0;
		for (j = 1; j < (variables.N * variables.M); j++)
		{	
			tem_chave = 0;
			returnVertex(maze, variables, &x, &y, aux->adjacency[j][i]);

			if (maze->mapa[x][y].caracter == 'E')
			{
				break;
			}
			else if (maze->mapa[x][y].n == grafo->inicio)
			{
				dist[i] = 999;
				break;
			}
			else if (maze->mapa[x][y].caracter == '.')
			{
				dist[i]++;
			}
			else if (maze->mapa[x][y].caracter == 'c' || maze->mapa[x][y].caracter == 'd' || maze->mapa[x][y].caracter == 'h' || maze->mapa[x][y].caracter == 's')
			{
				if (qKeys < variables.T)
				{
					if (maze->mapa[x][y].caracter == 'c')
					{
						one->key[qKeys] = 'C';
					}
					else if (maze->mapa[x][y].caracter == 'd')
					{
						one->key[qKeys] = 'D';
					}
					else if (maze->mapa[x][y].caracter == 'h')
					{
						one->key[qKeys] = 'H';
					}
					else if (maze->mapa[x][y].caracter == 's')
					{
						one->key[qKeys] = 'S';
					}
					dist[i]++;
					qKeys++;
				}
				else
				{
					dist[i] = 999;
					break;
				}
			}
			else if (maze->mapa[x][y].caracter == 'C' || maze->mapa[x][y].caracter == 'D' || maze->mapa[x][y].caracter == 'H' || maze->mapa[x][y].caracter == 'S')
			{
				for (k = 0; k < qKeys; k++)
				{
					if (maze->mapa[x][y].caracter == one->key[k])
					{
						dist[i]++;
						tem_chave = 1;
						break;
					}
				}
				if (tem_chave == 0)
				{
					dist[i] = 999;
					break;
				}
			}
		}
	}
	
	distancia = dist[0];
	for (i = 0; i <= aux->caminhos; i++)
	{
		if (dist[i] < distancia)
		{
			distancia = dist[i];
		}
	}
	if (distancia == 999)
	{
		printf("-1\n");
	}
	else
	{
		printf("%d\n", distancia);
	}
	free(one->key);
}

int returnVertex(Map *maze, Control variables, int *x, int *y, int n)
{
	int i, j;
	for (i = 0; i < variables.N; i++)
	{
		for (j = 0; j < variables.M; j++)
		{
			if (maze->mapa[i][j].n == n)
			{
				*x = i;
				*y = j;
				return 1;
			}
		}
	}
	return -1;
}