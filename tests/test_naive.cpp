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

	int n = 10'000;

	G = GenerateRandomEulerian(n, .005);

	Timer timer;
	timer.start();
	LinearList<Vertex> eulerianCycle = FleuryNaive(G);
	timer.stop();

	cout << timer << endl;

	// cout << eulerianCycle << endl;

	cout << "FIM DO ALGORITMO" << endl;

	return 0;
}

