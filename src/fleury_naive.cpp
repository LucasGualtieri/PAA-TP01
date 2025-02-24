#include "../include/fleury_naive.hpp"

#include "../DataStructures/include/stack/linkedStack.hpp"
#include "../DataStructures/include/matrix/matrix.hpp"
#include "../include/progressBar.hpp"

bool isBridge(const Edge& e, bool** visitedEdges, const Graph& G) {

	return false;

	LinkedStack<Vertex> stack;

	LinearList<bool> visited(G.n, false);

	visited[e.u] = true;

	for (Vertex v : G.neighbors(e.u)) {
		if (v != e.v) {
			stack.push(v);
			visited[v] = true;
		}
	}

	while (!stack.empty()) {

		Vertex u = stack.pop();

		for (Vertex v : G.neighbors(u)) {

			if (v == e.v) return false;

			if (!visited[v] && !visitedEdges[u][v]) {
				stack.push(v);
				visited[v] = true;
			}
		}
	}

	return true;
}

LinearList<Vertex> FleuryNaive(const Graph& G) {

	std::cout << "Density: " << G.density(8) << std::endl;

	std::cout << "Allocatin matrix" << std::endl;

	int i, j;

	bool** visitedEdges = (bool**)calloc(G.n, sizeof(bool*));

    if (visitedEdges == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    for (i = 0; i < G.n; i++) {

        visitedEdges[i] = (bool*)calloc(G.n, sizeof(bool));

        if (visitedEdges[i] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }

		if ((i % (G.n / 100)) == 0) {
			progressBar(i, 0, G.n);
		}
    }

	std::cout << "setting matrix" << std::endl;

	std::cout << "starting fleury naive" << std::endl;

	LinearList<Vertex> eulerianCycle(G.m + 1);
	LinearList<Vertex> D(G.n, 0);

	for (Vertex v : G.vertices()) {
		D[v] = G.degree(v);
	}

	// TODO: Jogar a funcao Random pro utils
	// Vertex x = Random(0, G.n - 1);
	Vertex u = 0;
	eulerianCycle += u;

	for (int i = 0; i < G.m; i++) {

		if ((i % (G.n / 100)) == 0) {
			progressBar(i, 0, G.m);
		}

		for (Vertex v : G.neighbors(u)) {

			Edge e = {u, v};

			if (!visitedEdges[u][v]) {

				if (!isBridge(e, visitedEdges, G) || D[u] == 1) {

					visitedEdges[u][v] = true;
					D[u]--, D[v]--;
					eulerianCycle += v;
					u = v;

					break;
				}
			}
		}
	}

    // Free the allocated memory
    for (i = 0; i < G.n; i++) {
        free(visitedEdges[i]);
    }

    free(visitedEdges);

	return eulerianCycle;
}
