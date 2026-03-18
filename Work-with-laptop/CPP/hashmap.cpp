#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../H/my_singleLink.h"

using namespace singleLinked;

typedef struct
{
    int size_el;
    void *data;
    int hash;
} HashBlock;

typedef struct
{
    List **baketArray;
    int capacity;
    int count;
} HashMap;

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

int hashCodeFirst(int byte)
{
    unsigned int hash = 5381;
    int c = byte % 10;

    while (byte)
    {
        hash = ((hash << 5) + hash) + c;
        hash ^= hash << 10;
        c = byte % 10;
        byte /= 10;
    }

    return hash;
}

int hashCodeSecond(char *byte, int size)
{
    int hash = 0;
    for (int i = 0; i < size; i++)
    {
        hash += byte[i];
        hash += hash << 13;
        hash ^= hash >> 8;
    }

    hash += hash << 3;
    hash ^= hash >> 5;
    return hash;
}
int hashCodeThird(char *byte, int size)
{
    int hash = 0;
    for (int i = 0; i < size; i++)
    {
        hash += byte[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 1;
    hash ^= hash >> 5;
    return hash;
}

void freeHashMap(HashMap *dict)
{
    for (int i = 0; i < dict->capacity; i++)
    {
        freeList(dict->baketArray[i]);
        free(dict->baketArray[i]);
    }
    free(dict->baketArray);
    dict->capacity = 0;
    free(dict);
}

int hashMapIndex(HashMap *dict, char *key)
{
    if (!dict || !key)
        return -1;

    int hash = hashCodeFirst(key, strlen(key));

    Element *curr = dict->baketArray[hash % dict->capacity]->first;
    if (!curr)
        return -1;
    int index = 0;
    HashBlock *hbCurr = (HashBlock *)curr->data;
    while (curr)
    {
        if (hbCurr->hash == hash)
            return index;
        curr = curr->next;
        hbCurr = (HashBlock *)curr->data;
        index++;
    }
    if (hbCurr->hash != hash)
        return -1;
    return index;
}

HashMap *initHashMap(int capacity)
{
    HashMap *hm = (HashMap *)malloc(sizeof(HashMap));
    if (hm == NULL)
    {
        return NULL;
    }

    List **baketArray = (List **)calloc(capacity, sizeof(List *));

    if (!baketArray)
    {
        free(hm);
        return NULL;
    }

    for (int i = 0; i < capacity; i++)
    {
        baketArray[i] = (List *)malloc(sizeof(List));

        if (!baketArray[i])
        {
            for (int j = 0; j < i; j++)
            {
                free(baketArray[j]);
            }

            free(baketArray);
            free(hm);
            return NULL;
        }

        baketArray[i]->first = NULL;
    }

    hm->baketArray = baketArray;
    hm->capacity = capacity;
    hm->count = 0;
    return hm;
}

HashMap *hashMapExpandCap(HashMap *oldDict)
{
    HashMap *newDict = initHashMap(oldDict->capacity * 2);
    if (!newDict)
        return NULL;
    for (int i = 0; i < oldDict->capacity; i++)
    {
        for (int j = lenSingleLink(oldDict->baketArray[i]) - 1; j >= 0; j--)
        {
            HashBlock *hb = (HashBlock *)getElem(oldDict->baketArray[i], j);
            int hash = hb->hash;
            addLast(newDict->baketArray[hash % newDict->capacity], hb);
            newDict->count++;
        }
    }
    freeHashMap(oldDict);
    return newDict;
}

HashMap *hashMapReduceCap(HashMap *oldDict)
{
    HashMap *newDict = initHashMap(oldDict->capacity / 2 + 1);
    if (!newDict)
        return NULL;
    for (int i = 0; i < oldDict->capacity; i++)
    {
        for (int j = lenSingleLink(oldDict->baketArray[i]) - 1; j >= 0; j--)
        {
            HashBlock *hb = (HashBlock *)getElem(oldDict->baketArray[i], j);
            int hash = hb->hash;
            addLast(newDict->baketArray[hash % newDict->capacity], hb);
            newDict->count++;
        }
    }
    freeHashMap(oldDict);
    return newDict;
}

int hashMapAdd(HashMap **dictPtr, char *key, void *data, int size_el)
{
    HashMap *dict = *dictPtr;
    if (!dictPtr || !key || !data || !dict)
        return 0;

    int hash = hashCodeFirst(key, strlen(key));

    if (hashMapIndex(dict, key) != -1)
        return 0;

    if ((dict->count + 1 > dict->capacity * 3 / 4) || lenSingleLink(dict->baketArray[hash % dict->capacity]) + 1 > 16)
    {
        dict = hashMapExpandCap(dict);
        if (!dict)
            return 0;
    }

    HashBlock *hb = (HashBlock *)malloc(sizeof(HashBlock));

    hb->data = malloc(size_el);
    hb->size_el = size_el;
    hb->hash = hash;

    memcpy(hb->data, data, size_el);
    addLast(dict->baketArray[hash % dict->capacity], hb);
    dict->count++;
    *dictPtr = dict;

    return 1;
}

int hashMapDelElement(List *l, int index)
{
    if (!l || index < 0 || index > lenSingleLink(l) - 1)
        return 0;
    if (l->first == NULL)
        return 0;

    if (index == 0)
    {
        Element *tmp = l->first;
        l->first = tmp->next;
        HashBlock *delHashBlock = (HashBlock *)tmp->data;
        free(delHashBlock->data);
        free(tmp);
        return 1;
    }

    Element *prev = l->first;
    int i = 0;
    while (prev->next != NULL && i < index - 1)
    {
        prev = prev->next;
        i++;
    }

    Element *to_delete = prev->next;
    prev->next = to_delete->next;
    HashBlock *delHashBlock = (HashBlock *)to_delete->data;
    free(delHashBlock->data);
    free(to_delete);
    return 1;
}

int hashMapTryDel(HashMap **dictPtr, char *key)
{
    HashMap *dict = *dictPtr;
    if (!dictPtr || !key || !dict)
        return 0;

    int hash = hashCodeFirst(key, strlen(key));
    if (lenSingleLink(dict->baketArray[hash % dict->capacity]) == 0)
    {
        return 0;
    }

    if ((dict->count -1 < dict->capacity * 1 / 4))
    {
        dict = hashMapReduceCap(dict);
        if (!dict)
            return 0;
    }

    hashMapDelElement(dict->baketArray[hash % dict->capacity], hashMapIndex(dict, key));
    dict->count--;
    *dictPtr = dict;
    return 1;
}

void *getHM(HashMap *dict, char *key)
{
    if (!dict || !key)
        return 0;

    int hash = hashCodeFirst(key, strlen(key));

    if (lenSingleLink(dict->baketArray[hash % dict->capacity]) == 0)
        return 0;

    Element *curr = dict->baketArray[hash % dict->capacity]->first;
    if (!curr)
        return 0;
    HashBlock *hbCurr = (HashBlock *)curr->data;

    while (curr)
    {
        if (hbCurr->hash == hash)
            break;

        curr = curr->next;
        hbCurr = (HashBlock *)curr->data;
    }
    if (hbCurr->hash != hash)
        return 0;
    return hbCurr->data;
}

int main()
{
    HashMap *HM = initHashMap(7);
    HashMap **dictPtr = &HM;
    char str[] = "Hello";
    char key1[] = "33";
    hashMapAdd(dictPtr, key1, str, sizeof(str));
    printf("Cap - %i\n", HM->capacity);

    int n = 1448;
    char key2[] = "33";
    hashMapAdd(dictPtr, key2, &n, sizeof(n));
    printf("Cap - %i\n", HM->capacity);

    char *el1 = (char *)getHM(HM, key1);

    printf("SOSI (string): %s\n", el1);

    int *el2 = (int *)getHM(HM, key2);

    printf("YO (int): %i\n", *el2);

    printf("Check 33 - %i\n", hashMapIndex(HM, key2));

    hashMapTryDel(dictPtr, key1);

    printf("Cap - %i\n", HM->capacity);

    printf("Check 33 - %i\n", hashMapIndex(HM, key1));

    freeHashMap(HM);
}