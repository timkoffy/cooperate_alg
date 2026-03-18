#pragma once
#include "stdio.h"
#include "stdlib.h"

namespace my_queue{

    typedef struct Element {
        int data;
        struct Element* prev;
        struct Element* next;
    } Element;

    typedef struct Queue {
        Element* first;
        Element* last;
    } Queue;

    void init(Queue* q, int data) {
        Element* el = (Element*)malloc(sizeof(Element));
        if (el == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        el->data = data;
        el->prev = NULL;
        el->next = NULL;

        if (q->first == NULL) {
            q->first = el;
            q->last = el;
        } else {
            el->prev = q->last;
            q->last->next = el;
            q->last = el;
        }
    }

    int pop(Queue* q) {
        if (q->first == NULL) {
            return -1;   // очередь пуста
        }
        Element* toDelete = q->first;
        int value = toDelete->data;

        if (q->first == q->last) {   // только один элемент
            q->first = NULL;
            q->last = NULL;
        } else {
            q->first = q->first->next;
            q->first->prev = NULL;
        }
        free(toDelete);
        return value;
    }

    void clear(Queue* q) {
        while (q->first != NULL) {
            pop(q);
        }
    }
}

