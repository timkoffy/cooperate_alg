#include <iostream>

#include "my_graph_adjlist.h"
#include "array.h"

using namespace MyGraphAdjList;
using namespace MyStack;
using namespace MyDynamicArray;

namespace MyEulerPath {
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

    // main.cpp \/ \/ \/
    // Graph *g = createGraph(6);
    //
    // tryAddUndirectedEdge(g, 0, 1, 0);
    // tryAddUndirectedEdge(g, 1, 2, 0);
    // tryAddUndirectedEdge(g, 2, 3, 0);
    // tryAddUndirectedEdge(g, 3, 0, 0);
    // tryAddUndirectedEdge(g, 1, 5, 0);
    // tryAddUndirectedEdge(g, 1, 4, 0);
    // tryAddUndirectedEdge(g, 5, 4, 0);
    //
    // printGraph(g);
    //
    // printf("\n");
    //
    // Array *path = MyEulerPath::EulerHirHolzer(g, 0);
    // for (int i = 0; i < path->size; i++) {
    //     printf("%d ", path->data[i]);
    // }
    //
    // freeArray(path);
    //
    // freeGraph(g);
}