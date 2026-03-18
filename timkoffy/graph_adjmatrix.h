#pragma once
#include<stdio.h>
#include<stdlib.h>

namespace MyGraphAdjMatrix {
    typedef struct {
        int** matrix;
        int vertCount;
    } Graph;

    Graph* createGraph(int vertCount) {
        Graph* g = (Graph*)malloc(sizeof(Graph));
        if (g == NULL) {
            return NULL;
        }

        g->vertCount = vertCount;

        g->matrix = (int**)malloc(sizeof(int*) * vertCount);
        if (g->matrix == NULL) {
            free(g);
            return NULL;
        }

        for (int i = 0; i < vertCount; i++) {
            g->matrix[i] = (int*)calloc(vertCount, sizeof(int));
            if (g->matrix[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(g->matrix[j]);
                }
                free(g->matrix);
                free(g);
                return NULL;
            }
        }
        return g;
    }

    int tryAddEdge(Graph* g, int from, int to) {
        if (from == to) return 0;

        if (from < 0 || from >= g->vertCount || to < 0 || to >= g->vertCount) {
            return 0;
        }

        g->matrix[from][to] = 1;
        g->matrix[to][from] = 1;

        return 1;
    }

    int tryDeleteEdge(Graph* g, int from, int to) {
        if (from == to) return 0;

        if (from < 0 || from >= g->vertCount || to < 0 || to >= g->vertCount) {
            return 0;
        }

        if (g->matrix[from][to] == 0 || g->matrix[to][from] == 0) {
            return 0;
        }

        g->matrix[from][to] = 0;
        g->matrix[to][from] = 0;

        return 1;
    }

    int tryAddVerticle(Graph* g) {
        int** tmp = (int**)realloc(g->matrix, (g->vertCount + 1) * sizeof(int*));
        if (tmp == NULL) {
            return 0;
        }

        tmp[g->vertCount] = (int*)calloc(g->vertCount + 1, sizeof(int));
        if (tmp[g->vertCount] == NULL) {
            g->matrix = tmp;
            return 0;
        }

        for (int i = 0; i < g->vertCount; i++) {
            int *tmp2 = (int*) realloc(tmp[i], (g->vertCount + 1) * sizeof(int));
            if (tmp2 == NULL) {
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

    int tryDeleteVerticle(Graph *g, int vert) {
        if (vert < 0 || vert >= g->vertCount) {
            return 0;
        }

        if (vert == g->vertCount - 1) {
            // просто переносим внутри строк и реаллочим g->matrix
        }

        for (int i = vert; i < g->vertCount - 1; i++) {
            g->matrix[i] = g->matrix[i + 1];
            for (int j = 0; j < g->vertCount - 1; j++) {
                g->matrix[i][j] = g->matrix[i][j + 1];
            }
        }
        g->matrix = (int**)realloc(g->matrix, (g->vertCount - 1) * sizeof(int));

        g->vertCount--;
        return 1;
    }

    int tryDepthSearchPath(Graph *g, int root, int target) {
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

    int tryBreadthSearchPath(Graph *g, int root, int target) {
        Queue* q = createQueue(sizeof(int));
        int visited[g->vertCount]{0};

        enqueue(q, &root);
        printf("[%d]", root);
        visited[root] = 1;

        while (q->count > 0) {
            int vert;
            dequeue(q, &vert);
            for (int i = 0; i < g->vertCount; i++) {
                if (i == vert) {
                    continue;
                }
                if (g->matrix[vert][i] != 0 && visited[i] == 0) {
                    if (i == target) {
                        printf("[%d]!", target);
                        freeQueue(q);
                        return 1;
                    }
                    enqueue(q, &i);
                    printf("[%d]", i);
                    visited[i] = 1;
                }
            }
        }
        freeQueue(q);
        return 0;
    }

    void printGraph(Graph *g) {
        printf("  ");
        for (int i = 0; i < g->vertCount; i++) {
            printf("%d ", i);
        }
        printf("\n");

        for (int i = 0; i < g->vertCount; i++) {
            printf("%d ", i);
            for (int j = 0; j < g->vertCount; j++) {
                printf("%d ", g->matrix[i][j]);
            }
            printf("\n");
        }
    }
}