#pragma once

#include "../graph_adjmatrix.h"

using namespace MyGraphAdjMatrix;
using namespace MyQueue;

void printBuffer(char **buffer, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", buffer[i][j]);
        }
        printf("\n");
    }
}

void renderGraph(Graph *g) {
    // todo: чекнуть на существование графа
    // todo: чекнуть на ацикличность + пока что на связность(потом можно будет и на несвязных)

    int h = 15;
    int w = 40;
    char **buffer = (char**)malloc(sizeof(char*) * h);
    for (int i = 0; i < h; i++) {
        buffer[i] = (char*)malloc(sizeof(char) * w);
        for (int j = 0; j < w; j++) {
            buffer[i][j] = ' ';
        }
    }

    int *countVertsOnLevel = (int*)calloc(g->vertCount, sizeof(int));
    int *levels = (int*)calloc(g->vertCount, sizeof(int));
    int *parent = (int*)malloc(g->vertCount * sizeof(int));

    int *widths = (int*)malloc(g->vertCount * sizeof(int));
    int *offsets = (int*)malloc(g->vertCount * sizeof(int));
    int *prevBro = (int*)malloc(g->vertCount * sizeof(int));
    // offsets - хранит отступы
    // widths - хранит относительные ширины
    // prevBro - хранит индексы вершин предыдущих братьев. если самый первый брат, то -1


    Queue *q = createQueue(sizeof(int));

    // находим корень
    int root = -1;
    for (int i = 0; i < g->vertCount; i++) {
        int semiDegreeZahoda = 0;
        for (int j = 0; j < g->vertCount; j++) {
            if (g->matrix[j][i] != 0) {
                semiDegreeZahoda++;
            }
        }
        if (semiDegreeZahoda == 0) {
            root = i;
            parent[root] = -1;
            prevBro[root] = -1;
            addQueue(q, &i);
            break;
        }
    }

    // BFS с заполнением высот каждой вершины
    int maxLevel = 0;
    while (q->count > 0) {
        int cur;
        removeQueue(q, &cur);
        int lastBro = -1;
        for (int i = 0; i < g->vertCount; i++) {
            if (i == cur) continue;
            if (g->matrix[cur][i] != 0) {
                addQueue(q, &i);
                parent[i] = cur;

                prevBro[i] = lastBro;
                lastBro = i;

                levels[i] = levels[cur] + 1;
                maxLevel = levels[i] > maxLevel ? levels[i] : maxLevel;
            }
        }
    }

    // заполняем ширины
    {
        int curLevel = maxLevel;
        while (curLevel >= 0) {
            for (int u = 0; u < g->vertCount; u++) {
                if (curLevel == levels[u]) {
                    int width = 0;
                    for (int v = 0; v < g->vertCount; v++) {
                        if (g->matrix[u][v] != 0) {
                            width += widths[v];
                        }
                    }
                    if (width == 0) {
                        widths[u] = 1;
                    } else {
                        widths[u] = width;
                    }
                }
            }
            curLevel--;
        }
    }

    // заполняем отступы
    for (int i = 0; i < g->vertCount; i++) {
        if (i == root) {
            offsets[i] = 0;
            continue;
        }
        if (prevBro[i] == -1) {
            offsets[i] = offsets[parent[i]];
            continue;
        }
        offsets[i] = offsets[prevBro[i]] + widths[prevBro[i]];
    }

    // заполняем буфер
    for (int i = 0; i < g->vertCount; i++) {
        buffer[levels[i]][offsets[i] * 2] = i + '0';
    }

    Helper::printArrayInt(levels, g->vertCount, "levels");
    Helper::printArrayInt(prevBro, g->vertCount, "prevBro");
    Helper::printArrayInt(widths, g->vertCount, "widths");

    // todo: стрелочки
    // todo: центрирование
    // todo: сжать буффер до минимально возможной высоты и ширины для экономии пространства в терминале

    printBuffer(buffer, h, w);

    free(buffer);
    free(levels);
}