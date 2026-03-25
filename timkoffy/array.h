#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace MyDynamicArray {
    typedef struct {
        int* data;           // Указатель на данные
        int capacity;        // Вместимость (выделенная память)
        int size;            // Текущий размер (количество элементов)
    } Array;

    // Создание массива с начальной вместимостью
    Array* createArray(int initialCapacity) {
        Array* arr = (Array*)malloc(sizeof(Array));
        if (!arr) return NULL;

        arr->data = (int*)malloc(sizeof(int) * initialCapacity);
        if (!arr->data) {
            free(arr);
            return NULL;
        }

        arr->capacity = initialCapacity;
        arr->size = 0;

        return arr;
    }

    // Создание пустого массива
    Array* createArray() {
        return createArray(4); // Начальная вместимость по умолчанию
    }

    // Увеличение вместимости массива
    int reserve(Array* arr, int newCapacity) {
        if (!arr) return 0;
        if (newCapacity <= arr->capacity) return 1;

        int* newData = (int*)realloc(arr->data, sizeof(int) * newCapacity);
        if (!newData) return 0;

        arr->data = newData;
        arr->capacity = newCapacity;
        return 1;
    }

    // Добавление элемента в конец
    int pushBack(Array* arr, int value) {
        if (!arr) return 0;

        // Если массив заполнен, увеличиваем вместимость в 2 раза
        if (arr->size >= arr->capacity) {
            int newCapacity = (arr->capacity == 0) ? 4 : arr->capacity * 2;
            if (!reserve(arr, newCapacity)) return 0;
        }

        arr->data[arr->size] = value;
        arr->size++;
        return 1;
    }

    // Удаление последнего элемента
    int popBack(Array* arr) {
        if (!arr || arr->size == 0) return 0;

        arr->size--;
        return 1;
    }

    // Вставка элемента по индексу
    int insertAt(Array* arr, int index, int value) {
        if (!arr) return 0;
        if (index < 0 || index > arr->size) return 0;

        // Увеличиваем размер при необходимости
        if (arr->size >= arr->capacity) {
            int newCapacity = (arr->capacity == 0) ? 4 : arr->capacity * 2;
            if (!reserve(arr, newCapacity)) return 0;
        }

        // Сдвигаем элементы вправо
        for (int i = arr->size; i > index; i--) {
            arr->data[i] = arr->data[i - 1];
        }

        arr->data[index] = value;
        arr->size++;
        return 1;
    }

    // Удаление элемента по индексу
    int removeAt(Array* arr, int index) {
        if (!arr || arr->size == 0) return 0;
        if (index < 0 || index >= arr->size) return 0;

        // Сдвигаем элементы влево
        for (int i = index; i < arr->size - 1; i++) {
            arr->data[i] = arr->data[i + 1];
        }

        arr->size--;
        return 1;
    }

    // Получение элемента по индексу
    int getAt(Array* arr, int index, int* outValue) {
        if (!arr || !outValue) return 0;
        if (index < 0 || index >= arr->size) return 0;

        *outValue = arr->data[index];
        return 1;
    }

    // Изменение элемента по индексу
    int setAt(Array* arr, int index, int value) {
        if (!arr) return 0;
        if (index < 0 || index >= arr->size) return 0;

        arr->data[index] = value;
        return 1;
    }

    // Поиск индекса первого вхождения значения
    int find(Array* arr, int value) {
        if (!arr) return -1;

        for (int i = 0; i < arr->size; i++) {
            if (arr->data[i] == value) return i;
        }

        return -1;
    }

    // Очистка массива (без освобождения памяти)
    void clear(Array* arr) {
        if (arr) arr->size = 0;
    }

    // Уменьшение вместимости до текущего размера
    int shrinkToFit(Array* arr) {
        if (!arr) return 0;
        if (arr->size == 0) {
            free(arr->data);
            arr->data = NULL;
            arr->capacity = 0;
            return 1;
        }

        int* newData = (int*)realloc(arr->data, sizeof(int) * arr->size);
        if (!newData) return 0;

        arr->data = newData;
        arr->capacity = arr->size;
        return 1;
    }

    // Получение текущего размера
    int getSize(Array* arr) {
        return arr ? arr->size : 0;
    }

    // Получение текущей вместимости
    int getCapacity(Array* arr) {
        return arr ? arr->capacity : 0;
    }

    // Проверка, пуст ли массив
    int isEmpty(Array* arr) {
        return arr ? (arr->size == 0) : 1;
    }

    // Освобождение памяти массива
    void freeArray(Array* arr) {
        if (arr) {
            if (arr->data) free(arr->data);
            free(arr);
        }
    }

    // Печать массива
    void printArray(Array* arr) {
        if (!arr) {
            printf("[]\n");
            return;
        }

        printf("[");
        for (int i = 0; i < arr->size; i++) {
            printf("%d", arr->data[i]);
            if (i < arr->size - 1) printf(", ");
        }
        printf("] (size=%d, capacity=%d)\n", arr->size, arr->capacity);
    }

    // Создание копии массива
    Array* copyArray(Array* src) {
        if (!src) return NULL;

        Array* dest = createArray(src->capacity);
        if (!dest) return NULL;

        // Копируем данные
        memcpy(dest->data, src->data, sizeof(int) * src->size);
        dest->size = src->size;

        return dest;
    }

    // Конкатенация двух массивов (добавляет arr2 в конец arr1)
    int concat(Array* arr1, Array* arr2) {
        if (!arr1 || !arr2) return 0;

        // Резервируем память под оба массива
        if (!reserve(arr1, arr1->size + arr2->size)) return 0;

        // Копируем элементы
        for (int i = 0; i < arr2->size; i++) {
            arr1->data[arr1->size + i] = arr2->data[i];
        }

        arr1->size += arr2->size;
        return 1;
    }
}