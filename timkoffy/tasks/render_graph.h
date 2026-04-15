    #pragma once

    #include "../data_structures/graph_adjmatrix.h"

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

    void removeAllCycles(Graph *g) {
        int *visited = (int*)calloc(g->vertCount, sizeof(int));
        int *prev = (int*)malloc(g->vertCount * sizeof(int));

        for (int i = 0; i < g->vertCount; i++) {
            prev[i] = -1;
        }

        Queue *q = createQueue(sizeof(int));

        int start = 0;
        addQueue(q, &start);

        while (q->count > 0) {
            int cur;
            removeQueue(q, &cur);

            for (int i = 0; i < g->vertCount; i++) {
                if (i == cur) {
                    continue;
                }

                if (g->matrix[cur][i] == 0) {
                    continue;
                }

                if (i == prev[cur]) {
                    tryDeleteEdge(g, cur, i);
                    continue;
                }

                if (visited[i] == 1) {
                    tryDeleteUnorderedEdge(g, cur, i);
                    continue;
                }

                addQueue(q, &i);
                prev[i] = cur;
                visited[i] = 1;
            }
        }
    }

    // вывод ориентированного графа-дерева
    void renderGraph(Graph *g) {
        if (g == nullptr) return;

        removeAllCycles(g);

        int *levels = (int*)calloc(g->vertCount, sizeof(int));
        int *parent = (int*)malloc(g->vertCount * sizeof(int));
        int *widths = (int*)calloc(g->vertCount, sizeof(int));
        int *offsets = (int*)calloc(g->vertCount, sizeof(int));
        int *prevBro = (int*)malloc(g->vertCount * sizeof(int));
        int *visited = (int*)calloc(g->vertCount, sizeof(int));

        // levels - хранит высоты каждой вершины
        // parent - хранит родителя каждой вершины
        // widths - хранит ширины узла с учетом своих детей
        // offsets - хранит отступы для вставки в буфер
        // prevBro - хранит индексы вершин предыдущих братьев. если самый первый брат, то -1
        // visited - хранит посетили вершниу или нет

        for (int i = 0; i < g->vertCount; i++) {
            parent[i] = -1;
            prevBro[i] = -1;
        }



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
                break;
            }
        }

        if (root == -1) {
            free(levels);
            free(parent);
            free(widths);
            free(offsets);
            free(prevBro);
            free(visited);
            printf("AAALARM CYCLE !! ALARM CYCLE !! ALARM CYCLE !!\n");
            return;
        }

        // BFS с заполнением высот каждой вершины
        int maxLevel = 0;
        {
            Queue *q = createQueue(sizeof(int));

            addQueue(q, &root);
            visited[root] = 1;

            while (q->count > 0) {
                int cur;
                removeQueue(q, &cur);
                int lastBro = -1;
                for (int i = 0; i < g->vertCount; i++) {
                    if (i == cur) continue;
                    if (g->matrix[cur][i] != 0) {
                        if (!visited[i]) {
                            addQueue(q, &i);
                            visited[i] = 1;

                            parent[i] = cur;
                            prevBro[i] = lastBro;
                            lastBro = i;

                            levels[i] = levels[cur] + 1;
                            maxLevel = levels[i] > maxLevel ? levels[i] : maxLevel;
                        }
                        else {
                            free(levels);
                            free(parent);
                            free(widths);
                            free(offsets);
                            free(prevBro);
                            freeQueue(q);
                            free(visited);
                            printf("ALARM CYCLE !! ALARM CYCLE !! ALARM CYCLE !!\n");
                            return;
                        }
                    }
                }
            }
            freeQueue(q);
        }

        // заполняем ширины
        for (int curLevel = maxLevel; curLevel >= 0; curLevel--) {
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
        }

        // заполняем отступы
        int updated = 1;
        while (updated) {
            updated = 0;
            for (int i = 0; i < g->vertCount; i++) {
                if (!visited[i] || i == root) continue;

                int newOffset;
                if (prevBro[i] == -1) {
                    newOffset = offsets[parent[i]];
                } else {
                    newOffset = offsets[prevBro[i]] + widths[prevBro[i]];
                }

                if (newOffset != offsets[i]) {
                    offsets[i] = newOffset;
                    updated = 1;
                }
            }
        }

        // считаем размеры буфера + инициализируем
        int w = 0;
        for (int i = 0; i < g->vertCount; i++) {
            if (offsets[i] * 4 > w) w = offsets[i] * 4;
        }
        w += 4;

        int h = maxLevel * 4 + 4;

        char **buffer = (char**)malloc(sizeof(char*) * h);
        for (int i = 0; i < h; i++) {
            buffer[i] = (char*)malloc(sizeof(char) * w);
            for (int j = 0; j < w; j++) {
                buffer[i][j] = ' ';
            }
        }

        // заполняем буфер
        for (int i = 0; i < g->vertCount; i++) {
            if (!visited[i]) continue;

            int row = levels[i] * 4;
            int col = offsets[i] * 4;
            col += widths[i] * 4 / 2;

            // buffer[row + 3][col-1] = '[';
            // buffer[row + 3][col] = i + 'A';
            buffer[row + 3][col] = i + 1 + '0';
            // buffer[row + 3][col+1] = ']';

            if (i == root) continue;

            int colParent = offsets[parent[i]] * 4;
            colParent += widths[parent[i]] * 4 / 2;

            buffer[row][colParent] = '|';
            buffer[row + 2][col] = '|';

            if (prevBro[i] == -1 && i != root) {
                buffer[row + 1][col] = '+';
                continue;
            }

            int j = col - 1;
            int prevBroCol = (offsets[prevBro[i]] * 4) + (widths[prevBro[i]] * 4 / 2);
            while (j > prevBroCol) {
                if (j == colParent) {
                    buffer[row + 1][j] = '+';
                } else {
                    buffer[row + 1][j] = '-';
                }
                j--;
            }

            buffer[row + 1][col] = '+';
        }

        // Helper::printArrayInt(levels, g->vertCount, "levels");
        // Helper::printArrayInt(prevBro, g->vertCount, "prevBro");
        // Helper::printArrayInt(widths, g->vertCount, "widths");
        // Helper::printArrayInt(offsets, g->vertCount, "offsets");
        // Helper::printArrayInt(parent, g->vertCount, "parent");
        // Helper::printArrayInt(visited, g->vertCount, "visited");

        printBuffer(buffer, h, w);

        for (int i = 0; i < h; i++) {
            free(buffer[i]);
        }
        free(buffer);
        free(levels);
        free(parent);
        free(widths);
        free(offsets);
        free(prevBro);
        free(visited);
    }
