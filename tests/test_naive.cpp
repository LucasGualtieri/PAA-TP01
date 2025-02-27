#include <iostream>

#include "../DataStructures/include/graph/Graph.hpp"
#include "../DataStructures/include/graph/GraphBuilder.hpp"
#include "../DataStructures/utils/timer.hpp"

#include "../include/fleury_naive.hpp"
#include "../include/RandomEulerian.hpp"

using namespace std;

int main() {

	Graph G = GraphBuilder()
		.dataStructure(Graph::FastAdjacencyList)
	.build();

	int n = 11;

	for (Vertex u = 0; u < n; u++) {
		G.addVertex(u);
	}

	G.addEdge({0, 1});
	G.addEdge({0, 10});
	G.addEdge({0, 9});
	G.addEdge({0, 7});
	G.addEdge({2, 6});
	G.addEdge({3, 4});
	G.addEdge({4, 1});
	G.addEdge({5, 3});
	G.addEdge({5, 8});
	G.addEdge({7, 2});
	G.addEdge({7, 6});
	G.addEdge({7, 8});
	G.addEdge({7, 10});

	Timer timer;

	timer.start();
	LinearList<Vertex> eulerianCycle = FleuryNaive(G);
	timer.stop();

	cout << timer << endl;

	cout << eulerianCycle << endl;

	G.export_to("tests/images/semi-eulerian-graph");

	cout << "FIM DO ALGORITMO" << endl;

	return 0;
}

