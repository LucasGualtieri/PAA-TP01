#include <iostream>

#include "../DataStructures/include/graph/Graph.hpp"
#include "../DataStructures/include/graph/GraphBuilder.hpp"

#include "../include/fleury_naive.hpp"
#include "../include/RandomEulerian.hpp"
#include "../include/progressBar.hpp"

using namespace std;

int main() {

	int n = 100'000;

	Graph G = GraphBuilder()
		.dataStructure(Graph::FastAdjacencyList)
	.build();

	for (Vertex v = 0; v < n; v++) {
		G.addVertex(v);
	}

	// Generating a regular eulerian degree n - 1 complete graph
	for (Vertex u = 0; u < n; u++) {
		for (Vertex v = u + 1; v < n; v++) {
			if (v % 10'000 == 0) G.addEdge({u, v});
		}
		if ((u % (n / 100)) == 0) {
			progressBar(u, 0, n);
		}
	}

	// Graph G = GenerateRandomEulerian(n, .005);

	cout << "G density: " << G.density(20) << endl;
	cout << "G m: " << G.m << endl;

	LinearList<Vertex> eulerianCycle = FleuryNaive(G);

	cout << "ALL DONE!" << endl;

	// cout << eulerianCycle << endl;

	return 0;
}
