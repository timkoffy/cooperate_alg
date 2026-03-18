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
}