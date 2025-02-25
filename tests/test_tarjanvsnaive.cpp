#include <iostream>

#include "../DataStructures/utils/timer.hpp"
#include "../DataStructures/include/graph/Graph.hpp"
#include "../DataStructures/include/graph/GraphBuilder.hpp"

#include "../include/RandomEulerian.hpp"

#include "../include/fleury_naive.hpp"
#include "../include/fleury_tarjan.hpp"

using namespace std;

int main() {

	Graph G = GraphBuilder()
		.dataStructure(Graph::FastAdjacencyList)
	.build();

	int n = 1'000;

	G = GenerateRandomEulerian(n, .90);

	LinearList<Vertex> eulerianCycle;

	Timer timer;

	timer.start();
	eulerianCycle = FleuryTarjan(G);
	timer.stop();

	cout << endl << timer << endl;

	timer.start();
	eulerianCycle = FleuryNaive(G);
	timer.stop();

	cout << endl << timer << endl;

	cout << "FIM DO ALGORIMTO" << endl;

	return 0;
}
