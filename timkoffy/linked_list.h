#pragma once
#include <cstdio>
#include <cstring>

namespace MyLinkedList {
    typedef struct Item {
        void *data;
        Item *next;
    } Item;

    typedef struct {
        Item *first;
        Item *last;
        int sizeVar;
    } List; 

    List* createList(int sizeVar) {
        List *list = (List*)malloc(sizeof(List));
        if (list == nullptr) {
            return nullptr;
        }
        list->sizeVar = sizeVar;
        list->first = nullptr;
        list->last = nullptr;
        return list;
    }

    int tryAppendList(List *list, void *src) {
        // проверка на наличие списка
        if (list == nullptr) {
            return 0;
        }
        Item *item = (Item*)malloc(sizeof(Item));
        if (item == nullptr) {
            return 0;
        }

        // заполняем элемент, передаем указатель на фактические данные, аллоцируемые извне
        item->data = src;
        item->next = nullptr;

        // если список пустой
        if (list->first == nullptr) {
            list->first = item;
            list->last = item;
            return 1;
        }

        // если есть хотя бы один элемент
        list->last->next = item;
        list->last = item;
        return 1;
    }

    int tryInsertList(List *list, void *src, int index) {
        // проверка на наличие списка и валидность индекса
        if (list == nullptr || index < 0) {
            return 0;
        }
        Item *item = (Item*)malloc(sizeof(Item*) + list->sizeVar);
        if (item == nullptr) {
            return 0;
        }

        // заполняем элемент, передаем указатель на фактические данные, аллоцируемые извне
        item->data = src;

        // вставка в начало
        if (index == 0) {
            item->next = list->first;
            list->first = item;
            return 1;
        }

        // проход до элемента перед нужным элементом
        Item* ptr = list->first;
        for (int i = 0; i < index - 1; i++) {
            ptr = ptr->next;
            // если индекс больше фактического колва элементов
            if (ptr->next == nullptr) {
                return 0;
            }
        }
        // вставляем в список, обновляя указатели
        item->next = ptr->next;
        ptr->next = item;
        return 1;
    }

    int tryRemoveLastList(List *list) {
        if (list == nullptr) return 0;
        Item *ptr = list->first;

        // если только один элемент
        if (list->first == list->last) {
            free(list->first->data);
            free(list->first);
            list->first = nullptr;
            list->last = nullptr;
            return 1;
        }

        // проходим до предпоследнего элемента
        while (ptr->next != list->last) {
            ptr = ptr->next;
        }

        free(list->last->data);
        free(list->last);
        ptr->next = nullptr;
        list->last = ptr;
        return 1;
    }

    int tryGetByIndexList(List *list, void *dest, int index) {
        // проверка на наличие хотя бы одного элемента в списке
        // и на валидность индекса
        if (list == nullptr || list->first == nullptr || index < 0) return 0;

        Item *ptr = list->first;
        // поулчение первого элемента
        if (index == 0) {
            memcpy(dest, ptr->data, list->sizeVar);
            return 1;
        }
        // проход до элемента перед нужным элементом
        for (int i = 0; i < index - 1; i++) {
            ptr = ptr->next;
            // если индекс больше фактического колва элементов
            if (ptr->next == nullptr) {
                return 0;
            }
        }
        memcpy(dest, ptr->next->data, list->sizeVar);
        return 1;
    }

    void printListInt(List *list) {
        if (list == nullptr || list->first == nullptr || list->sizeVar != sizeof(int)) return;

        Item *ptr = list->first;
        int value;
        printf("[");
        while (ptr->next != nullptr) {
            memcpy(&value, ptr->data, list->sizeVar);
            printf("%d, ", value);
            ptr = ptr->next;
        }
        memcpy(&value, ptr->data, list->sizeVar);
        printf("%d]", value);
    }

    // void freeList(List *list) {
    //     if (list == nullptr) return;
    //     Item *ptr = list->first;
    //     // очищаем данные в каждом элементе списка + сам элемент
    //     // проходимся до последнего элемента
    //     printf("\n");
    //     while (ptr != nullptr) {
    //         Item *tmp = ptr->next;
    //         printf("!");
    //         if (ptr->data != nullptr) {
    //             free(ptr->data);
    //         }
    //         free(ptr);
    //         ptr = tmp;
    //     }
    //     printf("\n");
    //     free(list);
    // }
}