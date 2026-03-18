#pragma once
#include <cstdio>

#include "linked_list.h"

using namespace MyLinkedList;

namespace MyHashMapLinkedList {
    typedef struct {
        char* key;
        int value;
    } Entry;

    typedef struct {
        List *bucketArray;
        int count;
        int capacity;
    } HashMap;

    // вставка в хешмапу
    // хеш функция
    // расширение капасити
    // удаление из хешмапы
    // получение значения по ключу

    HashMap *createHashMap(int size) {
        HashMap *hashMap = (HashMap*)malloc(sizeof(HashMap));
        hashMap->capacity = size;
        hashMap->count = 0;
        for (int i = 0; i < size; i++) {
            hashMap->bucketArray = createList(sizeof(Entry));
        }
    }
}
