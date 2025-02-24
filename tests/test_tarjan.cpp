#include <iostream>

#include "../DataStructures/include/graph/Graph.hpp"
#include "../DataStructures/include/graph/GraphBuilder.hpp"

#include "../include/fleury_tarjan.hpp"

using namespace std;

int main() {

	Graph G = GraphBuilder()
		.dataStructure(Graph::FastAdjacencyList)
	.build();

	int n = 3;

	for (Vertex v = 0; v < n; v++) {
		G.addVertex(v);
	}

	// Generating a regular eulerian degree n - 1 complete graph
	for (Vertex u = 0; u < n; u++) {
		for (Vertex v = u + 1; v < n; v++) {
			G.addEdge({u, v});
		}
	}

	LinearList<Vertex> eulerianCycle = FleuryTarjan(G);

	cout << eulerianCycle << endl;

	return 0;
}

