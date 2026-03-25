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

    void addQueue(Queue* q, void* data) {
        if (q == nullptr || data == nullptr) return;

        Item* item = (Item*)malloc(sizeof(Item));
        if (item == nullptr) return;

        item->data = malloc(q->sizeVar);
        if (item->data == nullptr) {
            free(item);
            return;
        }

        memcpy(item->data, data, q->sizeVar);
        item->next = nullptr;

        q->count++;

        // [0, 1, 2]
        if (q->end == nullptr) {
            q->first = item;
            q->end = item;
            return;
        }

        q->end->next = item;
        q->end = item;
    }

    int peekQueue(Queue* queue, void* out) {
        if (queue == NULL || queue->front == NULL || out == NULL) return 0;

        memcpy(out, queue->front->data, queue->size_el);
        return 1;
    }

    // Удаление элемента из начала очереди
    int dequeue(Queue* queue, void* out) {
        if (queue == NULL || queue->front == NULL) return 0;

        // Сохраняем данные, если нужен указатель на выход
        if (out != NULL) {
            memcpy(out, queue->front->data, queue->size_el);
        }

        // Сохраняем указатель на удаляемый узел
        Item* temp = queue->front;

        // Перемещаем указатель front на следующий элемент
        queue->front = queue->front->next;

        // Если очередь стала пустой, обнуляем и rear
        if (queue->front == NULL) {
            queue->rear = NULL;
        }

        // Освобождаем память
        free(temp->data);
        free(temp);

        queue->count--;
        return 1;
    }

    // Освобождение памяти очереди
    void freeQueue(Queue* queue) {
        if (queue) {
            clearQueue(queue);
            free(queue);
        }
    }
}