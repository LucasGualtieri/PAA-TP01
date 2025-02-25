#include <unordered_set>

#include "../include/fleury_tarjan.hpp"
// #include "../include/progressBar.hpp"
#include "../DataStructures/include/matrix/matrix.hpp"
#include "../include/progressBar.hpp"

struct EdgeHash {

    size_t operator()(const Edge& edge) const {

        size_t h1 = std::hash<Vertex>()(edge.u);
        size_t h2 = std::hash<Vertex>()(edge.v);

        return h1 ^ h2;
    }

};

void DFS(Vertex u, LinearList<int>& disc, LinearList<int>& low, LinearList<Vertex>& parent, Matrix<bool>& bridges, const Graph& G) {

	static int time = 0;

	disc[u] = low[u] = time++;

	for (Vertex v : G.neighbors(u)) {

		if (disc[v] == -1) {

			parent[v] = u;

			DFS(v, disc, low, parent, bridges, G);

			low[u] = std::min(low[u], low[v]);

			if (low[v] > disc[u]) {
				bridges[u][v] = true;
				bridges[v][u] = true;
			}
		}

		else if (v != parent[u]) low[u] = std::min(low[u], disc[v]);
	}
}

void Tarjan(Matrix<bool>& bridges, const Graph& G) {

	LinearList<int> disc(G.n, -1);
	LinearList<int> low(G.n, -1);
	LinearList<Vertex> parent(G.n, -1);

	for (int i = 0; i < G.n; i++) {
		for (int j = 0; j < G.n; j++) {
			bridges[i][j] = false;
		}
	}

	// Vertex x = Random(0, G.n - 1);
	Vertex x = 0;

	for (Vertex v : G.vertices()) {
		if (disc[v] == -1) {
			DFS(v, disc, low, parent, bridges, G);
		}
	}
}

LinearList<Vertex> FleuryTarjan(const Graph& G) {

	bool** visitedEdges = (bool**)calloc(G.n, sizeof(bool*));

	{
		std::cout << "Density: " << G.density(8) << std::endl;

		std::cout << "Allocatin matrix" << std::endl;

		if (visitedEdges == NULL) {
			perror("Memory allocation failed");
			return 1;
		}

		for (int i = 0; i < G.n; i++) {

			visitedEdges[i] = (bool*)calloc(G.n, sizeof(bool));

			if (visitedEdges[i] == NULL) {
				perror("Memory allocation failed");
				return 1;
			}

			// if ((i % (G.n / 100)) == 0) {
			// 	progressBar(i, 0, G.n);
			// }
		}

		std::cout << "setting matrix" << std::endl;

		std::cout << "starting fleury tarjan" << std::endl;
	}

	Matrix<bool> bridges(G.n, G.n);
	Tarjan(bridges, G);

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

		if (i % (G.m / 100) == 0) {
			progressBar(i, 0, G.m);
		}

		for (Vertex v : G.neighbors(u)) {

			if (!visitedEdges[u][v]) {

				if (!bridges[u][v] || D[u] == 1) {

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
    for (int i = 0; i < G.n; i++) {
        free(visitedEdges[i]);
    }

    free(visitedEdges);

	return eulerianCycle;
}
