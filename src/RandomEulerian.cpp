#include "../DataStructures/include/list/linearList.hpp"
#include "../DataStructures/include/graph/Graph.hpp"
#include "../DataStructures/include/graph/GraphBuilder.hpp"
#include "../DataStructures/utils/UnionFind.hpp"
#include "../DataStructures/utils/timer.hpp"

#include "../include/RandomEulerian.hpp"
#include "../include/colorMessages.hpp"
#include "../include/progressBar.hpp"
#include "../include/utils.hpp"

// TODO: Implementar com o esquema arvore geradora + rejection sampling
Graph GenerateRandomEulerian(size_t n, float density) {

	float minDensity = (2.0 * n - 2) / (n * n - n);

	if (density < minDensity) {
		throw std::runtime_error(std::format("Density must be greater than {}", minDensity));
	}

	if (n % 2 == 0 && density == 1) {
		throw std::runtime_error(std::format("Density must be less than {} for even values of N", 1));
	}

	std::cout << "Generating a Random Eulerian Graph" << std::endl;

	Timer timer;

	timer.start();

	Graph G = GraphBuilder()
		.dataStructure(Graph::FastAdjacencyList)
	.build();

	LinearList<Vertex> D(n, 0);
	UnionFind<Vertex> uf;

	for (Vertex v = 0; v < n; v++) {
		uf.insert(v);
		G.addVertex(v);
	}

	int k = n + ((n % 2) - 2);

	int contador = 0, colisions = 0;
	int m = ((n * n - n) / 2.0) * density;

	// WARNING: sera que existe a chance desse while rodar pra sempre?
	// for (int i = 0; i < Kn && G.density() < density; i++) {
	// while (|Cc| > 1) { ... } // For large values of n its very likely
	while (contador < m) {

		Vertex u = Random(0, n - 1);
		Vertex v = Random(0, n - 1);

		if (u != v && !G.hasEdge({v, u}) && D[u] < k && D[v] < k) {

			uf.join(u, v);
			G.addEdge({u, v});
			D[u]++, D[v]++;

			if (contador % (m / 100) == 0) {
				progressBar(contador, 0, m);
			}

			contador++;
		}

		else {
			colisions++;
			// std::cout << "colisaoooooo!" << std::endl;
			// if (contador++ == 100'000'000) {
			// 	std::cout << "contador: " << contador << std::endl;
			// }
		}
	}

	// std::cout << std::fixed << std::setprecision(4);  // Set to 4 decimal places
	// std::cout << "\nG.n: " << G.n << std::endl;
	// std::cout << "G.m: " << G.m << std::endl;
	std::cout << "colisions: " << colisions << std::endl;
	std::cout << "G.density(): " << G.density() << std::endl;
	// std::cout << "O(3n²): " << (3*n*n) << std::endl;

	// TODO:
	if (uf.numberOfSets() > 1) {

		std::cout << "Nao e um grafo conexo" << std::endl;

		// for (Vertex v : uf.heads()) {
		//
		// }
	}

	// LinearList<Vertex> oddDegree(n);
	//
	// for (Vertex v : G.vertices()) {
	// 	if (D[v] % 2 == 1) oddDegree += v;
	// }
	//
	// for (int i = 0; i < oddDegree.size(); i += 2) {
	//
	// 	Vertex u = oddDegree[i], v = oddDegree[i + 1];
	//
	// 	if (!G.hasEdge({u, v})) {
	// 		G.addEdge({u, v});
	// 		D[u]++, D[v]++;
	// 	}
	//
	// 	else if (D[u] == 1 || D[v] == 1) {
	//
	// 		Vertex w;
	//
	// 		for (Vertex x : G.vertices()) {
	// 			if (D[x] % 2 == 0 && D[x] < k - 1) {
	// 				w = x;
	// 				break;
	// 			}
	// 		}
	//
	// 		G.addEdge({u, w});
	// 		G.addEdge({w, v});
	//
	// 		D[u]++, D[v]++, D[w] += 2;
	// 	}
	//
	// 	else {
	// 		G.removeEdge({u, v});
	// 		D[u]--, D[v]--;
	// 	}
	// }
	//
	// bool aux = false;
	//
	// for (Vertex v : G.vertices()) {
	// 	if (D[v] % 2 == 1) {
	// 		aux = true;
	// 		std::cout << std::format("D[{}]: {}", v, D[v]) << std::endl;
	// 	}
	// }
	//
	// if (!aux) {
	// 	// std::cout << "E euleriano!!!" << std::endl;
	// }
	//
	// else std::cout << "Nao e euleriano :(" << std::endl;

    Color red = {255, 0, 0};
    Color green = {0, 255, 0};

	printColoredMessage(green, red, 0.0, 10, timer.result(), std::format("{}s", timer.result()));

	return G;
}

Graph FastGenerateRandomEulerian(size_t n, float density) {

	float minDensity = (2.0 * n - 2) / (n * n - n);

	if (density < minDensity) {
		throw std::runtime_error(std::format("Density must be greater than {}", minDensity));
	}

	if (n % 2 == 0 && density == 1) {
		throw std::runtime_error("Density must be less than 1 for even values of N");
	}

	std::cout << "Generating a Random Eulerian Graph" << std::endl;

	Timer timer;

	timer.start();

	Graph G = GraphBuilder()
		.dataStructure(Graph::AdjacencyMatrix)
	.build();

	LinearList<Vertex> D(n, 0);
	UnionFind<Vertex> uf;

	for (Vertex v = 0; v < n; v++) {
		uf.insert(v);
		G.addVertex(v);
		progressBar(v, 0, n);
	}

	int k = n + ((n % 2) - 2);
	int m = ((n * n - n) / 2.0) * density;

	LinearList<Edge> edges(m);
	int contador = 0;

	for (int u = 0; contador < m && u < n - 1; u++) {
		for (int v = u + 1; contador < m && v < n; v++) {
			// edges += {u, v};
			G.addEdge({u, v});
			contador++;
			progressBar(contador, 0, m);
		}
	}

	//    for (int i = m - 1; i >= 0; i--) {
	//
	// 	std::swap(edges[i], edges[Random(0, i)]);
	//
	// 	Vertex u = edges[i].u;
	// 	Vertex v = edges[i].v;
	//
	// 	G.addEdge({u, v});
	// 	uf.join(u, v);
	// 	D[u]++, D[v]++;
	// 	progressBar((m - 1) - i, n - 1, m);
	// }

	std::cout << "G.density(): " << G.density() << std::endl;

	// TODO:
	if (uf.numberOfSets() > 1) {

		std::cout << "Nao e um grafo conexo" << std::endl;

		// for (Vertex v : uf.heads()) {
		//
		// }
	}

	else {
		std::cout << "É um grafo conexo!" << std::endl;
	}

	// LinearList<Vertex> oddDegree(n);
	//
	// for (Vertex v : G.vertices()) {
	// 	if (D[v] % 2 == 1) oddDegree += v;
	// }
	//
	// for (int i = 0; i < oddDegree.size(); i += 2) {
	//
	// 	Vertex u = oddDegree[i], v = oddDegree[i + 1];
	//
	// 	if (!G.hasEdge({u, v})) {
	// 		G.addEdge({u, v});
	// 		D[u]++, D[v]++;
	// 	}
	//
	// 	else if (D[u] == 1 || D[v] == 1) {
	//
	// 		Vertex w;
	//
	// 		for (Vertex x : G.vertices()) {
	// 			if (D[x] % 2 == 0 && D[x] < k - 1) {
	// 				w = x;
	// 				break;
	// 			}
	// 		}
	//
	// 		G.addEdge({u, w});
	// 		G.addEdge({w, v});
	//
	// 		D[u]++, D[v]++, D[w] += 2;
	// 	}
	//
	// 	else {
	// 		G.removeEdge({u, v});
	// 		D[u]--, D[v]--;
	// 	}
	// }
	//
	// bool aux = false;
	//
	// for (Vertex v : G.vertices()) {
	// 	if (D[v] % 2 == 1) {
	// 		aux = true;
	// 		std::cout << std::format("D[{}]: {}", v, D[v]) << std::endl;
	// 	}
	// }
	//
	// if (!aux) {
	// 	std::cout << "É euleriano!!!" << std::endl;
	// }
	//
	// else std::cout << "Não é euleriano :(" << std::endl;


    Color red = {255, 0, 0};
    Color green = {0, 255, 0};

	printColoredMessage(green, red, 0.0, 10, timer.result(), std::format("{}s", timer.result()));

	return G;
}
