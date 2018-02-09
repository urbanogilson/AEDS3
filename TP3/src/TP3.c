#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "TP3.h"

void allocGrid(Grid *map, Control variables)
{
	int i, j;
	map->matrix = (int**) malloc(variables.M * sizeof(int*));
	for (i = 0; i < variables.M; i++)
	{
		map->matrix[i] = (int*) malloc(variables.N * sizeof(int));
		for (j = 0; j < variables.N; j++)
		{
			map->matrix[i][j] = 0;
		}
	}
}

void freeGrid(Grid *map, Control variables)
{
	int i;
	for (i = 0; i < variables.M; i++)
	{
		free(map->matrix[i]);
	}
	free(map->matrix);
}

void getGrid(Grid *map, Control variables)
{
	int i, j;
	for (i = 0; i < variables.M; i++)
	{
		for (j = 0; j < variables.N; j++)
		{
			scanf("%d", &map->matrix[i][j]);
		}
	}
}

int max(int a, int b)
{
	if (a < b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

void *sumLine(void *argumentos)
{
	Arg *arg;
	arg = (Arg*)argumentos;
	int line = arg->line;
	Control variables = arg->variables;
	Grid map = arg->map;

	int aux[variables.N + 2];
	aux[variables.N] = 0;
	aux[variables.N + 1] = 0;

	int i;

	for (i = variables.N - 1; i >= 0; i--)
	{
		aux[i] = max(aux[i + 2] + map.matrix[line][i], aux[i + 1]);
	}

	arg->sum = aux[0];

	pthread_exit((void*)NULL);
}