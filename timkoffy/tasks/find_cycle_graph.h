#pragma once
#include "../graph_adjmatrix.h"
#include "../my_stack.h"

using namespace MyGraphAdjMatrix;
using namespace MyStack;

int isCyclicGraphUtil(Graph *g, int *visited, int cur) {
    if (visited[cur] == 1) {
        printf("   res %d\n", cur);
        return 1;
    }
    printf("   cur %d\n", cur);
    visited[cur] = 1;

    for (int i = 0; i < g->vertCount; i++) {
        if (i == cur) continue;
        if (g->matrix[cur][i] != 0) {
            if (isCyclicGraphUtil(g, visited, i)) {
                printf("   cycle backtrack %d\n", cur);
                return 1;
            }
        }
    }
    visited[cur] = 0;
    return 0;
}

int isCyclicGraph(Graph *g, int start) {
    int *visited = (int*)calloc(g->vertCount, sizeof(int));

    if (visited == nullptr)
        return 0;

    for (int i = 0; i < g->vertCount; i++) {
        printf("cur %d\n", i);
        if (isCyclicGraphUtil(g, visited, i)) {
            free(visited);
            return 1;
        }
    }
    free(visited);
    return 0;
}