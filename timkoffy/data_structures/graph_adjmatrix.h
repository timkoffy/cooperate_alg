#pragma once
#include <climits>
#include<cstdio>

#include "hashmap.h"
#include "queue.h"
#include "stack.h"

namespace MyGraphAdjMatrix {
    typedef struct {
        int** matrix;
        int vertCount;
    } Graph;

    Graph* createGraph(int vertCount) {
        Graph* g = (Graph*)malloc(sizeof(Graph));
        if (g == nullptr) {
            return nullptr;
        }

        g->vertCount = vertCount;

        g->matrix = (int**)malloc(sizeof(int*) * vertCount);
        if (g->matrix == nullptr) {
            free(g);
            return nullptr;
        }

        for (int i = 0; i < vertCount; i++) {
            g->matrix[i] = (int*)calloc(vertCount, sizeof(int));
            if (g->matrix[i] == nullptr) {
                for (int j = 0; j < i; j++) {
                    free(g->matrix[j]);
                }
                free(g->matrix);
                free(g);
                return nullptr;
            }
        }
        return g;
    }

    int tryAddEdge(Graph* g, int from, int to, int weight) {
        if (from == to) return 0;

        if (from < 0 || from >= g->vertCount || to < 0 || to >= g->vertCount) {
            return 0;
        }

        g->matrix[from][to] = weight;

        return 1;
    }

    int tryAddEdge(Graph* g, int from, int to) {
        return tryAddEdge(g, from, to, 1);
    }

    int tryAddUnorderedEdge(Graph* g, int from, int to, int weight) {
        if (!tryAddEdge(g, from, to, weight)) {
            return 0;
        }
        g->matrix[to][from] = weight;
        return 1;
    }

    int tryAddUnorderedEdge(Graph* g, int from, int to) {
        return tryAddUnorderedEdge(g, from, to, 1);
    }

    int tryDeleteEdge(Graph* g, int from, int to) {
        if (from == to) return 0;

        if (from < 0 || from >= g->vertCount || to < 0 || to >= g->vertCount) {
            return 0;
        }

        if (g->matrix[from][to] == 0) {
            return 0;
        }

        g->matrix[from][to] = 0;

        return 1;
    }

    int tryDeleteUnorderedEdge(Graph* g, int from, int to) {
        if (!tryDeleteEdge(g, from, to)) {
            return 0;
        }
        g->matrix[to][from] = 0;
        return 1;
    }

    int tryAddVerticle(Graph* g) {
        int** tmp = (int**)realloc(g->matrix, (g->vertCount + 1) * sizeof(int*));
        if (tmp == nullptr) {
            return 0;
        }

        tmp[g->vertCount] = (int*)calloc(g->vertCount + 1, sizeof(int));
        if (tmp[g->vertCount] == nullptr) {
            g->matrix = tmp;
            return 0;
        }

        for (int i = 0; i < g->vertCount; i++) {
            int *tmp2 = (int*) realloc(tmp[i], (g->vertCount + 1) * sizeof(int));
            if (tmp2 == nullptr) {
                for (int j = 0; j < i; i++) {
                    tmp[j] = (int *) realloc(tmp[j], g->vertCount * sizeof(int));
                }
                free(tmp[g->vertCount]);
                tmp = (int **) realloc(tmp, g->vertCount * sizeof(int *));
                g->matrix = tmp;
                return 0;
            }
            tmp2[g->vertCount] = 0;
            tmp[i] = tmp2;
        }

        g->matrix = tmp;
        g->vertCount++;
        return 1;
    }

    void printGraph(Graph *g);

    int tryDeleteVerticle(Graph *g, int vert) {
        if (vert < 0 || vert >= g->vertCount) {
            return 0;
        }

        for (int i = 0; i < g->vertCount; i++) {
            for (int j = vert; j < g->vertCount - 1; j++) {
                g->matrix[i][j] = g->matrix[i][j + 1];
            }
            g->matrix[i] = (int*)realloc(g->matrix[i], (g->vertCount - 1) * sizeof(int));
        }

        free(g->matrix[vert]);
        for (int i = vert; i < g->vertCount - 1; i++) {
            g->matrix[i] = g->matrix[i + 1];
        }

        g->matrix = (int**)realloc(g->matrix, (g->vertCount - 1) * sizeof(int*));

        g->vertCount--;
        return 1;
    }

    int tryDepthSearchPath(Graph *g, int root, int target) {
        using namespace MyStack;
        Stack* s = createStack(10, sizeof(int));
        int visited[g->vertCount]{0};

        pushStack(s, &root);
        printf("[%d]", root);
        visited[root] = 1;

        while (s->count > 0) {
            int vert;
            popStack(s, &vert);
            for (int i = 0; i < g->vertCount; i++) {
                if (i == vert) {
                    continue;
                }
                if (g->matrix[vert][i] != 0) {
                    if (visited[i] == 0) {
                        if (i == target) {
                            printf("[%d]", i);
                            freeStack(s);
                            return 1;
                        }
                        pushStack(s, &i);
                        printf("[%d]", i);
                        visited[i] = 1;
                    }
                }
            }
        }
        freeStack(s);
        return 0;
    }

    int tryBreadthSearchPath(Graph *g, int start, int target) {
        using namespace MyQueue;
        Queue* q = createQueue(sizeof(int));
        int visited[g->vertCount]{0};

        addQueue(q, &start);
        visited[start] = 1;

        while (q->count > 0) {
            int cur;
            removeQueue(q, &cur);
            printf("%d \n", cur);
            for (int i = 0; i < g->vertCount; i++) {
                if (i == cur) continue;
                if (g->matrix[cur][i] != 0 && visited[i] == 0) {
                    if (i == target) {
                        printf("%d!\n", cur);
                        freeQueue(q);
                        return 1;
                    }
                    visited[i] = 1;
                    addQueue(q, &i);
                }
            }
        }
        freeQueue(q);
        return 0;
    }

    int tryFindShortestPathFordBellman(Graph *g, int start, int target) {
        if (start < 0 || start >= g->vertCount || target < 0 || target >= g->vertCount)
            return 0;

        int *dist = (int*)malloc(g->vertCount * sizeof(int));
        if (!dist) return 0;

        for (int i = 0; i < g->vertCount; i++)
            dist[i] = INT_MAX;
        dist[start] = 0;

        for (int k = 0; k < g->vertCount - 1; k++) {
            int updated = 0;
            for (int u = 0; u < g->vertCount; u++) {
                if (dist[u] == INT_MAX) continue;
                for (int v = 0; v < g->vertCount; v++) {
                    int w = g->matrix[u][v];
                    if (w == 0) continue;
                    if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        updated = 1;
                    }
                }
            }
            if (!updated) break;
        }

        int negCycle = 0;
        for (int u = 0; u < g->vertCount; u++) {
            if (dist[u] == INT_MAX) continue;
            for (int v = 0; v < g->vertCount; v++) {
                int w = g->matrix[u][v];
                if (w == 0) continue;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    negCycle = 1;
                    break;
                }
            }
            if (negCycle) break;
        }

        if (negCycle) {
            free(dist);
            return 0;
        }
        if (dist[target] == INT_MAX) {
            free(dist);
            return 0;
        }
        printGraph(g);
        printf("%d", dist[target]);
        free(dist);
        return 1;
    }

    int **findShortestPathsFloydWarshall(Graph *g) {
        int **matrix = (int**)malloc(g->vertCount * sizeof(int*));
        for (int i = 0; i < g->vertCount; i++) {
            matrix[i] = (int*)malloc(g->vertCount * sizeof(int));
            for (int j = 0; j < g->vertCount; j++) {
                if (i == j) {
                    matrix[i][j] = 0;
                    continue;
                }
                if (g->matrix[i][j] == 0) {
                    matrix[i][j] = INT_MAX;
                    continue;
                }
                matrix[i][j] = g->matrix[i][j];
            }
        }

        for (int k = 0; k < g->vertCount; k++) {

            for (int i = 0; i < g->vertCount; i++) {
                for (int j = 0; j < g->vertCount; j++) {
                    if (matrix[i][j] == INT_MAX) {
                        printf("? ");
                        continue;
                    }
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            int update = 0;
            for (int i = 0; i < g->vertCount; i++) {
                for (int j = 0; j < g->vertCount; j++) {
                    if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX
                        && matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                        update = 1;
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
            if (!update) break;
        }

        return matrix;
    }


    void printGraph(Graph *g) {
        printf("    ");
        for (int i = 0; i < g->vertCount; i++) {
            printf("%c ", i + 'A');
        }
        printf("\n");

        printf("    ");
        for (int i = 0; i < g->vertCount; i++) {
            printf("| ");
        }
        printf("\n");

        for (int i = 0; i < g->vertCount; i++) {
            printf("%c — ", i + 'A');
            for (int j = 0; j < g->vertCount; j++) {
                if (g->matrix[i][j] == 0) {
                    printf(". ");
                    continue;
                }
                printf("%d ", g->matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    void freeGraph(Graph *g) {
        for (int i = 0; i < g->vertCount; i++) {
            free(g->matrix[i]);
        }
        free(g->matrix);
        free(g);
    }
}