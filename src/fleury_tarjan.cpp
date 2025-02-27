#include "../include/fleury_tarjan.hpp"
#include "../DataStructures/include/matrix/matrix.hpp"
#include "../DataStructures/include/stack/linkedStack.hpp"
#include "../include/progressBar.hpp"
#include "../include/utils.hpp"

#include <format>

#define DEBUGGING true

void TarjanIterative(Matrix<bool>& bridges, Graph& G) {

	LinearList<int> disc(G.n, -1), low(G.n, -1), parent(G.n, -1);

	LinkedStack<Vertex> stack = { 0 };

	int time = 0;

	while (!stack.empty()) {

		Vertex u = stack.pop();

		if (disc[u] == -1) stack.push(u);

		for (Vertex v : G.neighbors(u)) {

			if (disc[v] == -1) {

				if (disc[u] == -1) {

					parent[v] = u;

					stack.push(v);
				}

				else {

					low[u] = std::min(low[u], low[v]);

					if (low[v] > disc[u]) {

						bridges[u][v] = true;
						bridges[v][u] = true;

						std::cout << std::format("{{{}, {}}} is a bridge!", u, v) << std::endl;

						if (DEBUGGING) {
							G.changeEdgeProps({u, v}, {"red", "dotted"});
						}
					}
				}
			}

			else if (v != parent[u]) low[u] = std::min(low[u], disc[v]);
		}

		if (disc[u] == -1) {
			disc[u] = low[u] = time++;
		}
	}
}

bool isBridge(const Edge& e, const Matrix<bool>& visitedEdges, const Graph& G) {

	LinkedStack<Vertex> stack;

	LinearList<bool> visited(G.n, false);

	visited[e.u] = true;

	for (Vertex v : G.neighbors(e.u)) {
		if (v != e.v && !visitedEdges[e.u][v]) {
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

void DFS(Vertex u, LinearList<int>& disc, LinearList<int>& low, LinearList<Vertex>& parent, Matrix<bool>& bridges, LinearList<bool>& articulationPoints, Graph& G) {

    static int time = 0;
    int children = 0;  // Count children in DFS tree

    disc[u] = low[u] = time++;

    for (Vertex v : G.neighbors(u)) {

        if (disc[v] == -1) {  // If v is not visited
            parent[v] = u;
            children++;

            DFS(v, disc, low, parent, bridges, articulationPoints, G);

            low[u] = std::min(low[u], low[v]);

            // Bridge condition
            if (low[v] > disc[u]) {

                bridges[u][v] = true;
                bridges[v][u] = true;

                if (DEBUGGING) {
                    std::cout << std::format("{{{}, {}}} is a bridge!", u, v) << std::endl;
                    G.changeEdgeProps({u, v}, {"red", "dotted"});
                }
            }

            // Articulation point conditions:
            // 1. Root with two or more children
            // 2. Non-root vertex where low[v] >= disc[u]
            if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {

                articulationPoints[u] = true;

                if (DEBUGGING) {
                    std::cout << std::format("{} is an articulation point!", u) << std::endl;
                    G.changeVertexProps(u, {"blue", ""});
                }
            }
        }

        // Update low value for back edges
        else if (v != parent[u]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}

void Tarjan(Matrix<bool>& bridges, LinearList<bool>& articulationPoints, Graph& G) {

	LinearList<int> disc(G.n, -1), low(G.n, -1), parent(G.n, -1);

	Vertex u = Random(0, G.n - 1);

	LinkedStack<Vertex> stack = { u };

	DFS(u, disc, low, parent, bridges, articulationPoints, G);
}

LinearList<Vertex> FleuryTarjan(Graph& G) {

	Matrix<bool> visitedEdges(true, G.n, G.n);

	Matrix<bool> bridges(true, G.n, G.n);
	LinearList<bool> articulationPoints(G.n, false);
	Tarjan(bridges, articulationPoints, G);

	LinearList<Vertex> eulerianCycle(G.m + 1);

	LinearList<Vertex> D(G.n, 0);

	for (Vertex v : G.vertices()) {
		D[v] = G.degree(v);
	}

	Vertex u = Random(0, G.n - 1);

	for (Vertex v : G.vertices()) {
		if (G.degree(v) % 2 == 1) {
			u = v;
			break;
		} 
	}

	eulerianCycle += u;

	for (int i = 0; i < G.m; i++) {

		// if (i % (G.m / 100) == 0) {
		// 	progressBar(i, 0, G.m);
		// }

		for (Vertex v : G.neighbors(u)) {

			if (!visitedEdges[u][v]) {

				bool bridge = bridges[u][v];

				if (D[u] > 1 && articulationPoints[v]) {
					bridge = isBridge({u, v}, visitedEdges, G);
				}

				if (D[u] == 1 || !bridge) {

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
