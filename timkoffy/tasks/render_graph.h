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

    Queue *q = createQueue(sizeof(int));

    // находим корень
    for (int i = 0; i < g->vertCount; i++) {
        int semiDegreeZahoda = 0;
        for (int j = 0; j < g->vertCount; j++) {
            if (g->matrix[j][i] != 0) {
                semiDegreeZahoda++;
            }
        }
        if (semiDegreeZahoda == 0) {
            addQueue(q, &i);
            break;
        }
    }

    // BFS с заполнением высот каждой вершины
    while (q->count > 0) {
        int cur;
        removeQueue(q, &cur);
        for (int i = 0; i < g->vertCount; i++) {
            if (i == cur) continue;
            if (g->matrix[cur][i] != 0) {
                addQueue(q, &i);
                levels[i] = levels[cur] + 1;
            }
        }
    }

    for (int i = 0; i < g->vertCount; i++) {
        int curLevel = levels[i];
        buffer[curLevel][countVertsOnLevel[curLevel] * 2] = i + '0';
        countVertsOnLevel[curLevel]++;
    }

    Helper::printArrayInt(levels, g->vertCount, "levels");

    // todo: сжать буффер до минимально возможной высоты и ширины для экономии пространства в терминале

    printBuffer(buffer, h, w);

    free(buffer);
    free(levels);
}