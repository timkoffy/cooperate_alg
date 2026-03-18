#include<stdio.h>
#include<stdlib.h>
#include"../H/my_stack.h"

using namespace MyStack;

typedef struct{
    int to;
    int weight;
}Edge;

typedef struct 
{
    Edge** vertArray;
    int* adjCount;
    int vertCount;
}Graph;

Graph* createGraph(int vertCount){
    Graph* g = (Graph*)malloc(sizeof(Graph));

    g->vertCount = vertCount;
    g->adjCount = (int*)calloc(vertCount, sizeof(int));
    g->vertArray = (Edge**)malloc(sizeof(Edge*)*vertCount);
    
    return g;
}

int tryAddEdge(Graph* g, int from, int to, int weight){
    Edge e = {to,from};

    for (int i = 0; i < g->adjCount[from]; i++){
        if (g->vertArray[from][i].to == to ) return 0;
    }

    g->adjCount[from]++;

    g->vertArray[from] = (Edge*)realloc(g->vertArray[from],sizeof(Edge)*g->adjCount[from]);
    if (g->vertArray[from] == NULL) return 0;
    g->vertArray[from][g->adjCount[from]-1] = e;
    return 1;
}

int DFS(Graph* g){
    Stack* s = createStack(g->vertCount,sizeof(int));
    int check[g->vertCount];
    int start;

}

