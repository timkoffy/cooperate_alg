#include "timkoffy/graph_adjmatrix.h"

int main() {
    using namespace MyGraphAdjMatrix;
    Graph *g = createGraph(6);

    tryAddEdge(g, 0, 1);
    tryAddEdge(g, 1, 2);
    tryAddEdge(g, 2, 4);
    tryAddEdge(g, 1, 4);
    tryAddEdge(g, 4, 5);

    printGraph(g);

    tryDeleteVerticle(g, 2);

    printGraph(g);

    freeGraph(g);
}
