#pragma once
#include "../data_structures/min_heap.h"

typedef struct {
    int **data;
    int height;
    int width;
} Field;

typedef struct {
    int x;
    int y;
} Dot;

void randomizeWalls(Field *field) {
    srand(100);
    for (int i = 0; i < field->height; i++) {
        for (int j = 0; j < field->width; j++) {
            field->data[i][j] = rand() % 100 / 70;
        }
    }
}

void loopPathFind(Field *field, Dot target) {
    Dot *closedSet = (Dot*)calloc(field->height, sizeof(Dot));
    using namespace MyMinHeap;
    MinHeap *openSet = initMinHeap(sizeof(Dot));

    Dot cur = {0, 0};
    pushMinHeap(openSet, &cur);
    while (openSet->count > 0) {
        Dot cur;
        popMinHeap(openSet, &cur);
        while (true) {

        }
    }

    free(closedSet);
}

Field *initField(int h, int w) {
    Field *field = (Field*)malloc(sizeof(Field));

    field->height = h;
    field->width = w;

    int **data = (int**)malloc(sizeof(int*) * h);
    for (int i = 0; i < h; i++) {
        data[i] = (int*)malloc(sizeof(int) * w);
    }

    field->data = data;

    return field;
}

void freeField(Field *field) {
    for (int i = 0; i < field->height; i++) {
        free(field->data[i]);
    }
    free(field->data);
    free(field);
}

void printField(Field *field) {
    for (int i = 0; i < field->height; i++) {
        for (int j = 0; j < field->width; j++) {
            field->data[i][j] == 1 ? printf("▓▓") : printf("░░");
        } printf("\n");
    }
}