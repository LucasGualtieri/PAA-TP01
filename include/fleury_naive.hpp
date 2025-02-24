#ifndef FLEURY_NAIVE
#define FLEURY_NAIVE

#include "../DataStructures/include/graph/Graph.hpp"
#include "../DataStructures/include/list/linearList.hpp"

LinearList<Vertex> FleuryNaive(const Graph& G);
bool isBridge(const Edge& e, bool** visitedEdges, const Graph& G);

#endif
