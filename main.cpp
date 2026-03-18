#include <iostream>

#include "timkoffy/my_graph_adjlist.h"
#include "timkoffy/array.h"

using namespace MyGraphAdjList;
using namespace MyStack;
using namespace MyDynamicArray;

int addUndirectedEdge(Graph* g, int u, int v, int weight) {
    int r1 = tryAddEdge(g, u, v, weight);
    int r2 = tryAddEdge(g, v, u, weight);
    return r1 && r2;
}

void removeUndirectedEdge(Graph* g, int u, int v) {
    removeEdge(g, u, v);
    removeEdge(g, v, u);
}

Array *EulerHirHolzer(Graph *g, int start) {
    Stack *s = createStack(g->vertCount, sizeof(int));
    Array *result = createArray(g->vertCount);

    pushStack(s, &start);

    while (s->count > 0) {
        int vert;
        peekStack(s, &vert);

        if (g->adjCount[vert] > 0) {
            int next = g->adjArray[vert][0].to;
            removeUndirectedEdge(g, vert, next);
            pushStack(s, &next);
        } else {
            popStack(s, &vert);
            pushBack(result, vert);
        }
    }
    freeStack(s);

    Array* finalResult = createArray(result->size);
    for (int i = result->size - 1; i >= 0; i--) {
        pushBack(finalResult, result->data[i]);
    }
    freeArray(result);
    return finalResult;
}

int main() {
    Graph *g = createGraph(6);

    addUndirectedEdge(g, 0, 1, 0);
    addUndirectedEdge(g, 1, 2, 0);
    addUndirectedEdge(g, 2, 3, 0);
    addUndirectedEdge(g, 3, 0, 0);
    addUndirectedEdge(g, 1, 5, 0);
    addUndirectedEdge(g, 1, 4, 0);
    addUndirectedEdge(g, 5, 4, 0);

    printGraph(g);

    printf("\n");

    Array *path = EulerHirHolzer(g, 0);
    for (int i = 0; i < path->size; i++) {
        printf("%d ", path->data[i]);
    }

    freeArray(path);

    freeGraph(g);
}
