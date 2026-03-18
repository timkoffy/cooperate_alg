 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../H/my_queue.h"
//Функции создания графа, с начальнаым количеством вершин без связи между собой

using namespace my_queue;

typedef struct{
    int** AdjMatrix;
    int countVert;
}Graph;


Graph* createGraph(int countVert){
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->countVert = countVert;

    g->AdjMatrix = (int**)malloc((countVert+1)*sizeof(int*));
    if (g->AdjMatrix == NULL){
        free(g->AdjMatrix);
        free(g);
        return NULL;
    }
    for (int i = 1; i < countVert+1; i++){
        g->AdjMatrix[i] = (int*)calloc((countVert+1),sizeof(int));
        if (!g->AdjMatrix[i]){ 
            for (int j = 1; j < i+1; j++){
                free(g->AdjMatrix[j]);
            }
            free(g->AdjMatrix);
            free(g);
            return NULL;
        }
    }
    return g;
}

int tryAddEdgeUnOri(Graph* g, int from, int to,int weight){
    if(from < 0 || to < 0 || from > g->countVert || to > g->countVert || to==from ) return 0;
    if (g->AdjMatrix[to][from] == 1 && g->AdjMatrix[from][to] == 1) return 0;

    g->AdjMatrix[to][from] = weight;
    g->AdjMatrix[from][to] = weight;

    return 1;
}

int tryDelEdgeUnOri(Graph* g, int from, int to,int weight){
    if(from < 0 || to < 0 || from > g->countVert || to > g->countVert || to == from) return 0;
    if (g->AdjMatrix[to][from] == 0 && g->AdjMatrix[from][to] == 0) return 0;

    g->AdjMatrix[to][from] = 0;
    g->AdjMatrix[from][to] = 0;

    return 1;
}

int tryAddEdgeOri(Graph* g, int from, int to,int weight){
    if(from < 0 || to < 0 || from > g->countVert || to > g->countVert || to==from ) return 0;
    if (g->AdjMatrix[to][from] == 1 && g->AdjMatrix[from][to] == 1) return 0;

    g->AdjMatrix[to][from] = weight;

    return 1;
}

int tryDelEdgeOri(Graph* g, int from, int to,int weight){
    if(from < 0 || to < 0 || from > g->countVert || to > g->countVert || to == from) return 0;
    if (g->AdjMatrix[to][from] == 0 && g->AdjMatrix[from][to] == 0) return 0;

    g->AdjMatrix[to][from] = 0;

    return 1;
}

int tryAddVert(Graph* g){
    int** tmp= (int**)realloc(g->AdjMatrix,sizeof(int*)*(g->countVert+2));
    if (tmp == NULL) return 0;
    for (int i = 1; i < g->countVert+1+1; i++){
        int* temp = (int*)realloc(g->AdjMatrix[i],(g->countVert+1+1)*sizeof(int));
        if (temp==NULL){
            for (int j = 1; j < i+1; j++)
            {
                g->AdjMatrix[j] = (int*)realloc(g->AdjMatrix[i],(g->countVert+1)*sizeof(int));
            }
            return 0;
        }
        temp[g->countVert] = 0;
        g->AdjMatrix[i] = temp;
    }
    g->countVert++;
    g->AdjMatrix = tmp;
    return 1;
}
int tryDelVert(Graph* g, int delVert){  
    int ok = 0;
    int** tmp = g->AdjMatrix;
    for (int i = 1; i < g->countVert+1; i++){
        int ok2 = 0;
        for (int j = 1; j < g->countVert+1; j++)
        {   
            if(j == delVert) ok2 = 1;

            if (ok2){
                tmp[i][j] = tmp[i][j+1];
            }
        }
        
        if(delVert == i) ok = 1;
        if (ok){
            tmp[i] = tmp[i+1];
        }
        tmp[i] = (int*)realloc(tmp[i],g->countVert*sizeof(int));
    }
    tmp = (int**)realloc(tmp,g->countVert*sizeof(int*));
    g->AdjMatrix = tmp;

    return 1;
    
}

void printGraph(Graph* g){
    printf("    ");
    for (int i = 1; i < g->countVert+1; i++){
        printf(" %i ",i);
    }
    printf("\n");

    for (int i = 1; i < g->countVert+1; i++){
        printf("%i - ",i);
        for (int j = 1; j < g->countVert+1; j++){
            printf(" %i ",g->AdjMatrix[i][j]);
        }
        printf("\n");
    }
    return;
}

int isDigit(char c){
    return '0'<=c&&c<='9';
}

int isListZero(int* list, int len){
    for (int i = 0; i < len; i++)
    {
        if (list[i] != 0) return 0;        
    }
    return 1;
    
}

int inList(int* list,int len, int el){
    for (int i = 0; i < len; i++)
    {
        if (list[i] == el) return 1;        
    }
    return 0;
}

int DFS(Graph* g, int point, int endPoint, int* visited){
    visited[point] = 1;
    if (point == endPoint) return 1;
    for (int i = 1; i < g->countVert+1; i++){
        if( g->AdjMatrix[point][i]==1 &&visited[i]==0) {
            return DFS(g,i,endPoint,visited);
        }
    }
    return 0;
    
}

int initDFS(Graph* g, int startPoint, int endPoint){
    int* visited = (int*)malloc(sizeof(int)*(g->countVert+1));
    for (int i = 1; i < g->countVert+1; i++)
    {
        visited[i] = 0;
    }
    return DFS(g,startPoint,endPoint,visited);
}

int neighbors(Graph* g, int point, Queue* q,int* visited){
    visited[point] = 1;
    for (int i = 1; i < g->countVert+1; i++){
        if(g->AdjMatrix[point][i]==1 && visited[i]==0) init(q,i);
    }
    return 0;
}

int initBFS(Graph* g, int startPoint, int endPoint){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    int* visited = (int*)malloc(sizeof(int)*(g->countVert+1));

    int point=startPoint;
    while (1){
        neighbors(g,point,q,visited);
        point=pop(q);
        if (point == endPoint) return 1;
    }
    return 0;
}

int main(){
    Graph* g = createGraph(6);
    tryAddEdgeUnOri(g,1,2,1);
    tryAddEdgeUnOri(g,1,3,1);
    tryAddEdgeUnOri(g,2,5,1);
    tryAddEdgeUnOri(g,5,6,1);
    tryAddEdgeUnOri(g,3,4,1);
    tryAddEdgeUnOri(g,4,6,1);
    printGraph(g);
    printf("\n%i",initBFS(g,1,6));
    
    return 1;
}