#include <format>

#include "../DataStructures/include/graph/Graph.hpp"
#include "../include/RandomEulerian.hpp"

using namespace std;

int main() {
	
	for (int N : { 100, 1'000, 10'000, 100'000 }) {

		for (float density : { 0.25, 0.50, 0.75 }) {

			for (int i = 0; i < 1; i++) {

				cout << format("Generating G({}, {})...", N, density) << endl;

				// NOTE: Se o custo de gerar a lista de arestas for O(3n²)
				// O que valera mais a pena, deixar o random fazer a braba, ou garantir?
				Graph G = GenerateRandomEulerian(N, density);

				cout << format("Density(G): {}", G.density()) << endl;

				// if (j == 0) G.export_to(format("images/random_graph_{}", counter++));
			}
		}
	}
}
