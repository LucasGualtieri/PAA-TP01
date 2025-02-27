#ifndef FLEURY_TARJAN
#define FLEURY_TARJAN

#include "../DataStructures/include/graph/Graph.hpp"
#include "../DataStructures/include/list/linearList.hpp"
#include "../DataStructures/include/matrix/matrix.hpp"

LinearList<Vertex> FleuryTarjan(Graph&);
bool isBridge(const Edge&, const Matrix<bool>&, const Graph&);

#endif
