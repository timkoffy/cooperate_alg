#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../H/my_stack.h"
//Функции создания графа, с начальнаым количеством вершин без связи между собой



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
        if (g->AdjMatrix[i]==NULL){
            for (int j = 0; j < i+1; j++)
            {
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

    g->AdjMatrix[to][from] = -1;
    g->AdjMatrix[from][to] = -1;

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

    g->AdjMatrix[to][from] = -1;

    return 1;
}

int tryAddVert(Graph* g){
    int** tmp= (int**)realloc(g->AdjMatrix,sizeof(int*)*(g->countVert+1+1));
    if (tmp == NULL) return 0;
    for (int i = 1; i < g->countVert+1+1; i++){
        int* temp = (int*)realloc(g->AdjMatrix[i],(g->countVert+2)*sizeof(int));

        if (temp==NULL){
            for (int j = 1; j < i+1; j++)
            {
                g->AdjMatrix[j] = (int*)realloc(g->AdjMatrix[i],(g->countVert+1)*sizeof(int));
            }
            return 0;
        }

        temp[g->countVert] = 0;
        tmp[i] = temp;
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
    for (int i = 1; i < g->countVert+1; i++){
        printf("%i - ",i);
        for (int j = 1; j < g->countVert+1; j++){
            printf("%i,",g->AdjMatrix[i][j]);
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

int DFS(Graph* g, int startPoint, int endPoint){
    if (startPoint==endPoint) return 1;
    else if (startPoint!=endPoint && isListZero(g->AdjMatrix[startPoint], g->countVert)) return 0;

    
} 

int main(){
    char str[20]="AAAAAAAABBBB"; //2023
    
    return 1;
}