#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char* bitarray;
    int size;
}Bloom;

int hashCodeFirst(char *byte, int size)
{
    int hash = 5381;
    for (int i = 0; i < size; i++)
    {
        hash = ((hash << 5) + hash) + byte[i];
        hash ^= hash << 10;
    }

    return hash < 0 ? -hash : hash;
}

int hashCodeSecond(char* byte, int size){
    int hash=0;
    for (int i = 0; i < size; i++)
    {
        hash += byte[i];
        hash+=hash<<13;
        hash^=hash>>8;
    }

    hash+=hash<<3;
    hash^=hash>>5;
    return hash;
}
int hashCodeThird(char* byte, int size){
    int hash=0;
    for (int i = 0; i < size; i++)
    {
        hash += byte[i];
        hash+=hash<<10;
        hash^=hash>>6;
    }

    hash+=hash<<1;
    hash^=hash>>5;
    return hash;
}
Bloom* createBF(int size){
    Bloom* retBloom = (Bloom*)calloc(size,1);
    char* array = (char*)calloc(size,1);

    retBloom->size = size;
    retBloom->bitarray = array;
    
    return retBloom;
}

void depBf(Bloom* b,char* data){
    int limitTable = b->size*8;
    int index = (hashCodeFirst(data,sizeof(data)) % (limitTable));
    b->bitarray[index/8] = b->bitarray[index/8] | (1<<index%8);

    index = (hashCodeSecond(data,sizeof(data)) % (limitTable));
    b->bitarray[index/8] = b->bitarray[index/8]|(1<<index%8);

    index = (hashCodeThird(data,sizeof(data)) % (limitTable));
    b->bitarray[index/8] = b->bitarray[index/8]|(1<<index%8);
    return;
}

int checkBF(Bloom* b, char* data){
    int checkResult = 1;
    int limitTable = b->size*8;

    int index = (hashCodeFirst(data,sizeof(data)) % (limitTable));
    checkResult = checkResult && (b->bitarray[index/8]&(1<<index%8));

    if(!checkResult) return checkResult;

    index = (hashCodeSecond(data,sizeof(data)) % (limitTable));
    checkResult = checkResult && (b->bitarray[index/8]&(1<<index%8));

    if(!checkResult) return checkResult;

    index = (hashCodeThird(data,sizeof(data)) % (limitTable));
    checkResult = checkResult && (b->bitarray[index/8]&(1<<index%8));

    if(!checkResult) return checkResult;

    return checkResult;
}

int main(){
    char* str1 = "123";
    char str2[3] = "Hu";

    printf("%i",hashCodeFirst);
    
}