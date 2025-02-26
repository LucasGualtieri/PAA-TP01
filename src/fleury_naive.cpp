#include "../include/fleury_naive.hpp"

#include "../DataStructures/include/stack/linkedStack.hpp"
#include "../DataStructures/include/matrix/matrix.hpp"
#include "../include/progressBar.hpp"
#include "../include/utils.hpp"

bool isBridge(const Edge& e, const Matrix<bool>& visitedEdges, const Graph& G) {

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

	Matrix<bool> visitedEdges(true, G.n, G.n);

	LinearList<Vertex> eulerianCycle(G.m + 1);
	LinearList<Vertex> D(G.n, 0);

	for (Vertex v : G.vertices()) {
		D[v] = G.degree(v);
	}

	Vertex u = Random(0, G.n - 1);
	eulerianCycle += u;

	for (int i = 0; i < G.m; i++) {

		if (i % (G.m / 100) == 0) {
			progressBar(i, 0, G.m);
		}

		for (Vertex v : G.neighbors(u)) {

			if (!visitedEdges[u][v]) {

				if (!isBridge({u, v}, visitedEdges, G) || D[u] == 1) {

					visitedEdges[u][v] = true;
					visitedEdges[v][u] = true;

					D[u]--, D[v]--;
					eulerianCycle += v;
					u = v;

					break;
				}
			}
		}
	}

	return eulerianCycle;
}
