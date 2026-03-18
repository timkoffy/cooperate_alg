#pragma once
#include <iostream>
#include <cstring>

namespace MyQueue {
    // Элемент очереди
    typedef struct Node {
        void* data;
        struct Node* next;
    } Node;

    // Структура очереди
    typedef struct {
        Node* front;    // указатель на начало очереди
        Node* rear;     // указатель на конец очереди
        int count;      // количество элементов
        int size_el;    // размер элемента
    } Queue;

    // Создание очереди
    Queue* createQueue(int size_el) {
        if (size_el <= 0) return NULL;

        Queue* queue = (Queue*)malloc(sizeof(Queue));
        if (queue == NULL) return NULL;

        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
        queue->size_el = size_el;

        return queue;
    }

    // Добавление элемента в конец очереди
    void enqueue(Queue* queue, void* value) {
        if (queue == NULL || value == NULL) return;

        // Создаем новый узел
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) return;

        // Выделяем память под данные
        newNode->data = malloc(queue->size_el);
        if (newNode->data == NULL) {
            free(newNode);
            return;
        }

        // Копируем данные
        memcpy(newNode->data, value, queue->size_el);
        newNode->next = NULL;

        // Если очередь пуста, новый элемент становится и началом и концом
        if (queue->rear == NULL) {
            queue->front = newNode;
            queue->rear = newNode;
        } else {
            // Иначе добавляем в конец
            queue->rear->next = newNode;
            queue->rear = newNode;
        }

        queue->count++;
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
        Node* temp = queue->front;

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

    // Получение количества элементов в очереди
    int lenQueue(Queue* queue) {
        if (queue == NULL) return 0;
        return queue->count;
    }

    // Проверка, пуста ли очередь
    int isEmptyQueue(Queue* queue) {
        return (queue == NULL || queue->count == 0);
    }

    // Очистка очереди (удаление всех элементов)
    void clearQueue(Queue* queue) {
        if (queue == NULL) return;

        Node* current = queue->front;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }

        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
    }

    // Освобождение памяти очереди
    void freeQueue(Queue* queue) {
        if (queue) {
            clearQueue(queue);
            free(queue);
        }
    }
}