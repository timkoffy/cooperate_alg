#pragma once
#include <cstdio>
#include <cstdlib>

#include "linked_list.h"
#include "helper.h"

using namespace MyLinkedList;

namespace MyHashMapLinkedList {
    typedef struct {
        char* key;
        int value;
    } Entry;

    typedef struct {
        List **bucketArray;
        int count;
        int capacity;
    } HashMap;

    // вставка в хешмапу
    // хеш функция
    // расширение капасити
    // удаление из хешмапы
    // получение значения по ключу
    // проверка на наличие в хешмапе

    HashMap *createHashMap(int size) {
        HashMap *hashMap = (HashMap*)malloc(sizeof(HashMap));
        hashMap->capacity = size;
        hashMap->count = 0;

        hashMap->bucketArray = (List**)malloc(size * sizeof(List*));

        for (int i = 0; i < size; i++) {
            hashMap->bucketArray[i] = createList(sizeof(Entry));
        }

        return hashMap;
    }

    unsigned int hashCodeFirst(char *str) {
        unsigned int hash = 5381;
        int i = 0;
        while (str[i] != '\0') {
            hash = (hash << 5) + hash + (unsigned int)(str[i]);
            i++;
        }
        return hash;
    }

    Entry *findEntryInList(List *bucket, char *key) {
        Item *cur = bucket->first;
        while (cur != nullptr) {
            Entry *entry = (Entry*)cur->data;
            int i = 0;
            int equal = 1;

            while (entry->key[i] != '\0' || key[i] != '\0') {
                if (entry->key[i] != key[i]) {
                    equal = 0;
                    break;
                }
                i++;
            }

            if (equal) {
                return entry;
            }
            cur = cur->next;
        }
        return nullptr;
    }

    void increaseCapacity(HashMap *hm) {
        int oldCapacity = hm->capacity;
        List **oldBucketArray = hm->bucketArray;
        int newCapacity = oldCapacity * 2;

        hm->bucketArray = (List**)malloc(newCapacity * sizeof(List*));
        hm->capacity = newCapacity;
        hm->count = 0;

        for (int i = 0; i < newCapacity; i++) {
            hm->bucketArray[i] = createList(sizeof(Entry));
        }


        for (int i = 0; i < oldCapacity; i++) {
            List *oldList = oldBucketArray[i];
            Item *cur = oldList->first;

            while (cur != nullptr) {
                Entry *entry = (Entry*)cur->data;

                unsigned int hash = hashCodeFirst(entry->key);
                int newIndex = hash % newCapacity;

                List *newBucket = hm->bucketArray[newIndex];

                tryAppendList(newBucket, entry);

                hm->count++;

                Item *next = cur->next;
                free(cur);
                cur = next;
            }
            free(oldList);
        }
        free(oldBucketArray);
    }

    void addToHashMap(HashMap *hm, char *key, int value) {
        if (hm->count + 1 == hm->capacity) {
            increaseCapacity(hm);
        }

        unsigned int hash = hashCodeFirst(key);
        int index = hash % hm->capacity;

        List *bucket = hm->bucketArray[index];

        Entry *entry = findEntryInList(bucket, key);

        if (entry != nullptr) {
            entry->value = value;
            return;
        }
        Entry *newEntry = (Entry*)malloc(sizeof(Entry));

        int len = 0;
        while (key[len] != '\0') {
            len++;
        }
        newEntry->key = (char*)malloc(len + 1);
        memcpy(newEntry->key, key, len);
        newEntry->key[len] = '\0';

        newEntry->value = value;

        Item *newItem = (Item*)malloc(sizeof(Item));
        newItem->data = newEntry;
        newItem->next = bucket->first;
        bucket->first = newItem;

        hm->count++;
    }

    int containsKey(HashMap *hm, char *key) {
        if (hm == nullptr || key == nullptr) return 0;

        unsigned int hash = hashCodeFirst(key);
        int index = hash % hm->capacity;

        List *bucket = hm->bucketArray[index];

        Entry *entry = findEntryInList(bucket, key);

        if (entry == nullptr) return 0;

        return 1;
    }

    int* getFromHashMap(HashMap *hm, char *key) {
        if (hm == nullptr || key == nullptr) return nullptr;

        unsigned int hash = hashCodeFirst(key);
        int index = hash % hm->capacity;

        List *bucket = hm->bucketArray[index];

        Entry *entry = findEntryInList(bucket, key);

        if (entry != nullptr) {
            return &entry->value;
        }

        return nullptr;
    }

    int tryRemoveFromHashMap(HashMap *hm, char *key) {
        if (hm == nullptr || key == nullptr) return 0;

        unsigned int hash = hashCodeFirst(key);
        int index = hash % hm->capacity;

        List *bucket = hm->bucketArray[index];

        Item *cur = bucket->first;
        Item *prev = nullptr;

        while (cur != nullptr) {
            Entry *entry = (Entry*)cur->data;

            int equal = Helper::cmpStr(entry->key, key);

            if (equal) {
                if (prev == nullptr) {
                    // если находим нужный сразу в начале бакета
                    bucket->first = cur->next;
                } else {
                    // если находим нужный в середине/конце бакета
                    prev->next = cur->next;
                }

                free(entry->key);
                free(entry);
                free(cur);
                hm->count--;

                return 1;
            }
            prev = cur;
            cur = cur->next;
        }
        return 0;
    }

    void printHashMap(HashMap *hm) {
        if (hm == nullptr) {
            return;
        }

        for (int i = 0; i < hm->capacity; i++) {
            List *bucket = hm->bucketArray[i];

            if (bucket == nullptr) return;

            Item *cur = bucket->first;
            while (cur != nullptr) {
                Entry *entry = (Entry*)cur->data;
                printf("%s: %d (лежит в %d)\n", entry->key, entry->value, i);
                cur = cur->next;
            }
        }
    }

    void freeHashMap(HashMap *hm) {
        for (int i = 0; i < hm->capacity; i++) {
            List *bucket = hm->bucketArray[i];

            Item *cur = bucket->first;
            while (cur != nullptr) {
                Item *next = cur->next;
                Entry *entry = (Entry*)cur->data;
                free(entry->key);
                free(entry);
                free(cur);
                cur = next;
            }
            free(bucket);
        }
        free(hm->bucketArray);
        free(hm);
    }
}
