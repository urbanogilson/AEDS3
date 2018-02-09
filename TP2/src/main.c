#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TP2.h"

int main()
{
	Player one;
	Map maze;
	Control variables;
	Graph grafo, caminhos, percursos;
	
	scanf("%d %d %d", &variables.N, &variables.M, &variables.T);

	createMap(&maze, variables); // Cria Mapa (labirinto)

	getMap(&maze, variables); // Pega a entrada (mapa)

	creatGraph(&grafo, variables); // Representação em Grafo

	insert(&maze, &grafo, variables); // Inserir todos os vértices e arestas
	
	creatGraph(&caminhos, variables); // Árvore de Caminhos

	creatPercursos(&percursos, variables); // Caminhos Possíveis

	buscaLargura(&maze, &grafo, &percursos, variables, grafo.inicio, &caminhos); // Gera caminhos e percursos possíveis

	VerificaCaminhos(&maze, &percursos, &grafo, &one, variables); // Verifica o menor caminho e imprime

	freeGraph(&percursos, variables); // Libera Percursos
	
	freeGraph(&caminhos, variables); // Libera Caminhos

	freeGraph(&grafo, variables); // libera representação por grafo

	freeMap(&maze, variables); // Libera memória do labirinto
	
	return 0;
}