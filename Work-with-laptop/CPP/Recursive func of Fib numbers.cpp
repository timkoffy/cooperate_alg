#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int* array;
    int size;
}Mem;


int recFib(int n){
    if (n==0) return 0;
    if (n==1) return 1;
    printf("*");
    return recFib(n-1)+recFib(n-2);
}

int memFib(int n, Mem** memo) {
    printf("*");
    if (n==0) return 0;
    if (n==1) return 1;

    Mem *mem = *memo;

    if (mem->size<=n){
        int oldSize = mem->size;
        mem->size = n+1;
        mem->array = (int*)realloc(mem->array,mem->size);
        if (!mem->array) exit(1);
        for (int i = oldSize; i < mem->size; i++) mem->array[i] = -1;
    }

    if(mem->array[n] == -1){
        mem->array[n] = memFib(n - 1, memo) + memFib(n - 2, memo);
    }

    return mem->array[n];
}

int main(){
    Mem* mem=(Mem*)malloc(sizeof(Mem));
    mem->array = NULL;
    mem->size = 0;
    printf("\n%i",recFib(30));
    printf("\n%i",memFib(30,&mem));
    
    
}