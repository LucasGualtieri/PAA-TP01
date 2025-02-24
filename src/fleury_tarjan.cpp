#include <unordered_set>

#include "../include/fleury_tarjan.hpp"

#include "../DataStructures/include/stack/linkedStack.hpp"

struct EdgeHash {

    size_t operator()(const Edge& edge) const {

        size_t h1 = std::hash<Vertex>()(edge.u);
        size_t h2 = std::hash<Vertex>()(edge.v);

        return h1 ^ h2;
    }

};

LinearList<Vertex> FleuryTarjan(const Graph& G) {

	std::unordered_set<Edge, EdgeHash> visitedEdges;
	LinearList<Vertex> eulerianCycle(G.m + 1);
	LinearList<Vertex> D(G.n, 0);

	for (Vertex v : G.vertices()) {
		D[v] = G.degree(v);
	}

	std::unordered_set<Edge, EdgeHash> bridges = Tarjan();

	// TODO: Jogar a funcao Random pro utils
	// Vertex x = Random(0, G.n - 1);
	Vertex u = 0;
	eulerianCycle += u;

	int walkedEdges = 0;

	while (walkedEdges < G.m) {

		for (Vertex v : G.neighbors(u)) {

			Edge e = {u, v};

			if (!visitedEdges.contains(e)) {

				if (!bridges.contains(e) || D[u] == 1) {
					visitedEdges.insert(e);
					D[u]--, D[v]--;
					u = v;
					break;
				}
			}
		}

		eulerianCycle += u;
		walkedEdges++;
	}

	return eulerianCycle;
}
