#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "TP3.h"

int main(int argc, char *argv[])
{
	Control variables;
	Grid map;
	scanf("%d %d", &variables.M, &variables.N);
	
	allocGrid(&map, variables);
	getGrid(&map, variables);

	int i, error = 0, num_threads = atoi(argv[1]), cont_create = 0, cont_join = 0;

	if (argc < 2)
	{
		printf("Falta parâmetro - Numero de Threads\n");
		return 1;
	}
	
	// Argumentos que vão trabalhar as linhas
	Arg *arg = (Arg*) malloc(variables.M * sizeof(Arg));

	pthread_t threads[num_threads];
	
	// Criação das threads
	while (cont_create < variables.M && num_threads > 0)
	{	
		cont_join = 0;
		if (num_threads > variables.M)
		{
			num_threads = variables.M;
		}
		for (i = 0; i < num_threads; i++)
		{
			arg[cont_create].line = cont_create;
			arg[cont_create].variables = variables;
			arg[cont_create].map = map;

			error = pthread_create(&threads[i], NULL, sumLine, (void*)&arg[cont_create]);
			if (error != 0)
			{
				printf("Falha na Criação\n");
				break;
			}
			cont_create++;
			cont_join++;
			if (cont_create == variables.M)
			{
				break;
			}
		}
		
		for (i = 0; i < cont_join; i++)
		{
			pthread_join(threads[i], NULL);
		}
	}

	// Coluna (Soma final)
	Arg final;
	final.line = 0;
	final.variables.N = variables.M;
	final.variables.M = 1;
	Grid map_final;
	allocGrid(&map_final, final.variables);

	for (i = 0; i < variables.M; i++)
	{
		map_final.matrix[0][i] = arg[i].sum;
	}

	final.map = map_final;

	pthread_t final_thread;
	pthread_create(&final_thread, NULL, sumLine, (void*)&final);
	pthread_join(final_thread, NULL);
	
	printf("%d\n", final.sum);
	
	free(arg);
	freeGrid(&map_final, final.variables);
	freeGrid(&map, variables);

	return 0;
}