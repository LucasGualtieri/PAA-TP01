#include <cmath>
// #include <iostream>

using namespace std;

// clear && g++ PAA-TP01.cc -std=c++23 && ./a.out

int main() {

	int n, m;
	// Graph G;

	for (int i = 1; i <= 5; i++) {

		n = pow(10, i);
		// m = ; // NOTE: Pensar na densidade do grafo

		auto [v, G] = GenerateRandomEulerianGraph(n, m);

		Fleury(v, DFS, G timer);

		log("Naive", timer);

		Fleury(v, Tarjan, G, timer);
		log("Tarjan", timer);

	}

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
