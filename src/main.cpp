#include <cmath>
#include <iostream>

using namespace std;

// #include "../include/fleury_naive.hpp"
// #include "../include/fleury_tarjan.hpp"
#include "../include/utils.hpp"

int main() {

	clearscreen();

	// Log naiveLog, tarjanLog;

	for (int N : { 100, 1'000, 10'000, 100'000 }) {

		for (float density : { 0.25, 0.50, 0.75 }) {

			for (int i = 0; i < 15; i++) {

				// Graph G = GenerateRandomEulerianGraph(N, density);

				// FleuryNaive(G, naiveLog);

				// FleuryTarjan(G, tarjanLog);
			}
		}
	}

	cout << "The LOG.csv file's been saved" << endl;

	return 0;
}

// TODO:
// Um log completo (igual TP de AEDs II) que nos permita salvar um CSV contendo
//  - Tempo
//  - Numero de operações?
//  - Numero de vertices
//  - Numero de arestas
//  - Densidade do Grafo
//  - Qual algortimo foi usado
//  Usar todas essas informacoes pra gerar varios graficos
// Colocar todo o codigo que esta dentro do for dentro de mais um for para pegar media?
