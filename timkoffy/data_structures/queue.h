#pragma once
#include <cstring>
#include <iostream>

namespace MyQueue {
    typedef struct Item {
        void* data;
        Item* next;
    } Item;

    typedef struct {
        Item* first;
        Item* end;
        int count;
        int sizeVar;
    } Queue;

    Queue* createQueue(int sizeVar) {
        if (sizeVar <= 0) return nullptr;

        Queue* q = (Queue*)malloc(sizeof(Queue));
        if (q == nullptr) return nullptr;

        q->first = nullptr;
        q->end = nullptr;
        q->count = 0;
        q->sizeVar = sizeVar;

        return q;
    }

    void addQueue(Queue* q, void* src) {
        if (q == nullptr || src == nullptr) return;

        Item* item = (Item*)malloc(sizeof(Item));
        if (item == nullptr) return;

        item->data = malloc(q->sizeVar);
        if (item->data == nullptr) {
            free(item);
            return;
        }

        memcpy(item->data, src, q->sizeVar);
        item->next = nullptr;

        q->count++;

        if (q->end == nullptr) {
            q->first = item;
            q->end = item;
            return;
        }

        q->end->next = item;
        q->end = item;
    }

    int peekQueue(Queue* q, void* dest) {
        if (q == nullptr || q->first == nullptr || dest == nullptr) return 0;

        memcpy(dest, q->first->data, q->sizeVar);
        return 1;
    }

    int removeQueue(Queue* q, void* dest) {
        if (q == nullptr || q->first == nullptr) return 0;

        if (dest != nullptr) {
            memcpy(dest, q->first->data, q->sizeVar);
        }

        Item* tmp = q->first;
        q->first = q->first->next;

        if (q->first == nullptr) {
            q->end = nullptr;
        }

        free(tmp->data);
        free(tmp);

        q->count--;
        return 1;
    }

    void freeQueue(Queue* q) {
        if (q != nullptr) {
            Item *ptr = q->first;
            for (int i = 0; i < q->count; i++) {
                Item *tmp = ptr->next;
                free(ptr->data);
                free(ptr);
                ptr = tmp;
            }
            free(q);
        }
    }
}