#pragma once
#include "../graph_adjmatrix.h"
#include "../my_stack.h"

using namespace MyGraphAdjMatrix;
using namespace MyStack;

// void findAllCyclesUtil(Graph *g, int *visited, int *path, int depth, int start, int cur) {
//     visited[cur] = 1;
//     path[depth] = cur;
//
//     for (int i = 0; i < g->vertCount; i++) {
//         if (i == cur) continue;
//         if (g->matrix[cur][i] != 0) {
//             if (i == start) { // нашли цикл, тк i замкнулось
//                 printf("   CYCLE: ");
//                 for (int j = 0; j <= depth; j++) {
//                     printf("%d ", path[j]);
//                 }
//                 printf("%d\n", i);
//                 continue;
//             }
//             if (i > start) { // проверка чтобы не было дублирования циклов
//                              // (считаем что вершины до start обработаны)
//                 if (visited[i] == 0) {
//                     findAllCyclesUtil(g, visited, path, depth + 1, start, i);
//                 } else {
//                     // встретили ребро которое входит в вершину
//                     // которая уже находится в текущем пути
//                 }
//             }
//         }
//     }
//     visited[cur] = 0;
// }

void printPath(int *path,int depth, int loopVert) {
    printf("CYCLE: ");
    for (int j = 0; j <= depth; j++) {
        printf("%d ", path[j]);
    }
    printf("%d\n", loopVert);
}

void findAllCyclesUtil(Graph *g, int *visited, int *path, int depth, int start, int cur) {
    visited[cur] = 1;
    path[depth] = cur;

    for (int i = start; i < g->vertCount; i++) {
        if (i == cur) continue;
        if (g->matrix[cur][i] != 0) {
            if (i == start) {
                printPath(path, depth, i);
                continue;
            }
            if (visited[i] == 0) {
                findAllCyclesUtil(g, visited, path, depth + 1, start, i);
            }
        }
    }
    visited[cur] = 0;
}


void findAllCycles(Graph *g) {
    int *visited = (int*)calloc(g->vertCount, sizeof(int));
    int *path = (int*)malloc(g->vertCount * sizeof(int));

    if (!visited || !path) {
        free(visited);
        free(path);
        return;
    }

    for (int i = 0; i < g->vertCount; i++) {
        findAllCyclesUtil(g, visited, path, 0, i, i);
    }
    free(visited);
}