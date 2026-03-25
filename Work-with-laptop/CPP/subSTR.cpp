#include <stdio.h>
#include <stdlib.h>
#include "../H/my_singleLink.h"

using namespace singleLinked;
typedef struct
{
    int size_el;
    void *data;
    int hash;
    int count;
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
        if (!curr)
            return -1;
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
    return newDict;
}

int hashMapAdd(HashMap **dictPtr, char *key, void *data, int size_el)
{
    if (!dictPtr || !key || !data)
        return 0;

    HashMap *dict = *dictPtr;
    if (!dict)
        return 0;

    int hash = hashCodeFirst(key, strlen(key));
    int index = hashMapIndex(dict, key);
    if (index != -1)
    {
        HashBlock *HB = (HashBlock *)getElem(dict->baketArray[hash % dict->capacity], index);
        if (HB->hash == hash)
        {
            HB->count++;
            return 1;
        }
    }

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
    hb->count = 1;

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
    free(delHashBlock);
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

    if ((dict->count - 1 < dict->capacity * 1 / 4))
    {
        dict = hashMapReduceCap(dict);
        if (!dict)
            return 0;
    }
    int index = hashMapIndex(dict, key);
    if (index == -1)
        return 0;
    hashMapDelElement(dict->baketArray[hash % dict->capacity], index);
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
        if (!curr)
            return 0;
        hbCurr = (HashBlock *)curr->data;
    }
    if (hbCurr->hash != hash)
        return 0;
    return hbCurr->data;
}

int printDict(HashMap *dict)
{
    int count = 0;
    for (int i = 0; i < dict->capacity; i++)
    {
        int lenCurrentElement = lenSingleLink(dict->baketArray[i]);
        for (int j = 0; j < lenCurrentElement; j++)
        {
            HashBlock *HB = (HashBlock *)getElem(dict->baketArray[i], j);
            printf("%s -> %i\n", (char *)HB->data, HB->count);
            count++;
        }
    }
    return count;
}

char *subString(char *str, int start, int end)
{
    int write = 0;
    char *ret = (char *)malloc(end - start + 1);
    for (int read = start; read < end; read++)
    {
        ret[write++] = str[read];
    }
    ret[write] = '\0';
    return ret;
}

void allSubString(HashMap **dict, char *str)
{
    int indexStart = 0;
    int lenStr = strlen(str);
    while (str[indexStart] != '\0')
    {
        int indexInside = lenStr;
        while (indexInside != indexStart)
        {
            char *sub = subString(str, indexStart, indexInside);
            printf("%s\n", sub);
            hashMapAdd(dict, sub, sub, strlen(sub) + 1);
            free(sub);
            indexInside--;
        }
        indexStart++;
    }
    printf("-------------------------------------\n");
}

int main()
{
    HashMap *HM = initHashMap(7);

    allSubString(&HM, "ababc");

    printf("\n%i\n", printDict(HM));

    freeHashMap(HM);
}