#pragma once
#include <cstdio>
#include <cstdlib>

#include "my_stack.h"

namespace MyGraphAdjList {
    typedef struct {
        int to;
        int weight;
    } Edge;

    typedef struct {
        Edge** adjArray;
        int* adjCount;
        int vertCount;
    } Graph;

    Graph* createGraph(int vertCount){
        Graph* g = (Graph*)malloc(sizeof(Graph));

        g->vertCount = vertCount;
        g->adjCount = (int*)calloc(vertCount, sizeof(int));
        g->adjArray = (Edge**)malloc(sizeof(Edge*)*vertCount);

        return g;
    }

    int tryAddEdge(Graph* g, int from, int to, int weight){
        Edge e = {to,weight};

        for (int i = 0; i < g->adjCount[from]; i++){
            if (g->adjArray[from][i].to == to ) {
                printf("ребро %d-%d уже существует\n", from, to);
                return 0;
            }
        }

        g->adjCount[from]++;
        g->adjArray[from] = (Edge*)realloc(g->adjArray[from],sizeof(Edge)*g->adjCount[from]);
        if (g->adjArray[from] == NULL)
            return 0;

        g->adjArray[from][g->adjCount[from]-1] = e;
        return 1;
    }

    void printGraph(Graph* g) {
        for (int i = 0; i < g->vertCount; i++) {
            printf("%d -> ", i);
            for (int j = 0; j < g->adjCount[i]; j++) {
                printf("%d(%d) ", g->adjArray[i][j].to, g->adjArray[i][j].weight);
            } printf("\n");
        }
    }

    void freeGraph(Graph* g) {
        for (int i = 0; i < g->vertCount; i++) {
            free(g->adjArray[i]);
        }
        free(g->adjArray);
        free(g->adjCount);
        free(g);
    }

    int DFS(Graph* g, int start, int target){
        using namespace MyStack;
        int* visitedVertices = (int*)calloc(g->vertCount, sizeof(int));
        Stack* s = createStack(g->vertCount,sizeof(int));

        pushStack(s, &start);
        visitedVertices[start] = 1;

        int curVert;
        while (s->count > 0) {
            popStack(s, &curVert);

            if (curVert == target) {
                freeStack(s);
                free(visitedVertices);
                return 1;
            }

            for (int i = 0; i < g->adjCount[curVert]; i++) {
                int neighbor = g->adjArray[curVert][i].to;
                if (!visitedVertices[neighbor]) {
                    visitedVertices[neighbor] = 1;
                    pushStack(s, &neighbor);
                }
            }
        }
        freeStack(s);
        free(visitedVertices);
        return 0;
    }


    // рекурсивный поиск в глубину
    // int DFS(Graph* g, int* checkedVertices, int curVert, int target){
    //     if (curVert == target) return 1;
    //     if (checkedVertices[curVert]) return 0;
    //
    //     checkedVertices[curVert] = 1;
    //     for (int i = 0; i < g->adjCount[curVert]; i++) {
    //         int neighbor = g->adjArray[curVert][i].to;
    //         if (!checkedVertices[neighbor]) {
    //             int reached = DFS(g, checkedVertices, neighbor, target);
    //             if (reached) return 1;
    //         }
    //     }
    //     return 0;
    // }
}