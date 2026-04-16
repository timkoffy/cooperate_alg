#pragma once

#include <sys/ioctl.h>

#include "../data_structures/min_heap.h"

typedef struct {
    int **wallData;
    int height;
    int width;
} Field;

typedef struct Dot {
    int x;
    int y;
    int g;
    int h;
    int f;
    Dot *prev;
} Dot;

Field *initField(int h, int w) {
    Field *field = (Field*)malloc(sizeof(Field));

    field->height = h;
    field->width = w;

    int **data = (int**)malloc(sizeof(int*) * h);
    for (int i = 0; i < h; i++) {
        data[i] = (int*)malloc(sizeof(int) * w);
    }

    field->wallData = data;

    return field;
}

void randomizeWalls(Field *field) {
    srand(time(nullptr));
    for (int i = 0; i < field->height; i++) {
        for (int j = 0; j < field->width; j++) {
            field->wallData[i][j] = rand() % 100 / 80;
            // field->wallData[i][j] = 0;
        }
    }
    field->wallData[field->height-1][field->width-1] = 0;
}

#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[40m"
#define COLOR_RED     "\033[41m"
#define COLOR_YELLOW  "\033[43m"
#define COLOR_BLUE    "\033[44m"

void printField(Field *field, Dot *cur, int startX, int startY, int targetX, int targetY, int **closedSet, int **openSet, int **pathMap) {
    system("sleep 0.03");
    printf("\033[2J\033[H");
    for (int i = 0; i < field->height; i++) {
        for (int j = 0; j < field->width; j++) {
            if (i == startY && j == startX) {
                printf(COLOR_RED "  " COLOR_RESET);
                continue;
            }
            if (i == targetY && j == targetX) {
                printf(COLOR_YELLOW "  " COLOR_RESET);
                continue;
            }
            if (i == cur->y && j == cur->x) {
                printf("►◄");
                continue;
            }
            if (pathMap[i][j] == 1) {
                printf(COLOR_BLUE "  " COLOR_RESET);
                continue;
            }
            if (field->wallData[i][j] == 1) {
                printf("██");
                continue;
            }
            if (openSet[i][j] == 1) {
                printf("▒▒");
                continue;
            }
            if (closedSet[i][j] == 1) {
                printf("░░");
                continue;
            }
            printf(COLOR_BLACK "  " COLOR_RESET);

        } printf("\n");
    }
    // printf("cur.g = %d, cur.h = %d, cur.f = %d\n", cur->g, cur->h, cur->f);
}

int compare(const void *a, const void *b) {
    return (*(Dot**)a)->h - (*(Dot**)b)->h;
}

int h(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

int **reconstructPath(Field *field, int startX, int startY, Dot *target) {
    int **pathMap = (int**)malloc(field->height * sizeof(int*));
    for (int i = 0; i < field->height; i++) {
        pathMap[i] = (int*)calloc(field->width, sizeof(int));
    }

    Dot *cur = target;
    while (cur != nullptr) {
        pathMap[cur->y][cur->x] = 1;
        cur = cur->prev;
    }

    return pathMap;
}

Dot **saveDot(Dot **allDots, int *dotsCount, int *capacityAllDots, Dot *dot) {
    allDots[(*dotsCount)++] = dot;
    if (*dotsCount + 1 > *capacityAllDots) {
        *capacityAllDots *= 2;
        Dot **newAllDots = (Dot**)realloc(allDots, *capacityAllDots * sizeof(Dot*));
        return newAllDots;
    }
    return allDots;
}

Dot *createDot(int x, int y, int g, int targetX, int targetY, Dot ***allDots, int *dotsCount, int *capacityAllDots, Dot *prev) {
    Dot *dot = (Dot*)malloc(sizeof(Dot));
    dot->x = x;
    dot->y = y;
    dot->g = g;
    dot->h = h(x, y, targetX, targetY);
    dot->f = dot->g + dot->h;
    dot->prev = prev;
    *allDots = saveDot(*allDots, dotsCount, capacityAllDots, dot);
    return dot;
}

void loopPathFind(Field *field, int startX, int startY, int targetX, int targetY) {
    int **closedSet = (int**)malloc(field->height * sizeof(int*));
    int **openSetForPrint = (int**)malloc(field->height * sizeof(int*));
    int **gMatrix = (int**)malloc(field->height * sizeof(int*));

    int capacityAllDots = 10;
    Dot** allDots = (Dot**)malloc(capacityAllDots * sizeof(Dot*));
    int dotsCount = 0;

    for (int i = 0; i < field->height; i++) {
        closedSet[i] = (int*)calloc(field->width, sizeof(int));
        openSetForPrint[i] = (int*)calloc(field->width, sizeof(int));
        gMatrix[i] = (int*)malloc(field->width * sizeof(int));
        for (int j = 0; j < field->width; j++) {
            gMatrix[i][j] = INT_MAX;
        }
    }

    using namespace MyMinHeap;
    MinHeap *openSet = initMinHeap(sizeof(Dot*), compare);

    Dot* start = createDot(startX, startY,
                    0,
                    targetX, targetY,
                    &allDots, &dotsCount, &capacityAllDots,
                    nullptr);

    gMatrix[startY][startX] = 0;
    pushMinHeap(openSet, &start);

    Dot* cur = nullptr;

    while (openSet->count > 0) {
        popMinHeap(openSet, &cur);

        int **pathMap = reconstructPath(field, startX, startY, cur);
        printField(field, cur, startX, startY, targetX, targetY, closedSet, openSetForPrint, pathMap);
        for (int i = 0; i < field->height; i++) {
            free(pathMap[i]);
        }
        free(pathMap);

        if (closedSet[cur->y][cur->x]) {
            continue;
        }

        openSetForPrint[cur->y][cur->x] = 0;
        closedSet[cur->y][cur->x] = 1;

        if (cur->x == targetX && cur->y == targetY) {
            break;
        }

        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++) {
            int neighX = cur->x + dx[i];
            int neighY = cur->y + dy[i];

            if (neighX < 0 || neighX >= field->width ||
                neighY < 0 || neighY >= field->height) {
                continue;
            }

            if (field->wallData[neighY][neighX] == 1) continue;
            if (closedSet[neighY][neighX]) continue;

            int tentativeG = cur->g + 1;

            if (tentativeG < gMatrix[neighY][neighX]) {
                gMatrix[neighY][neighX] = tentativeG;

                if (openSetForPrint[neighY][neighX]) {
                    continue;
                }

                Dot* neigh = createDot(neighX, neighY,
                    tentativeG,
                    targetX, targetY,
                    &allDots, &dotsCount, &capacityAllDots,
                    cur);

                openSetForPrint[neighY][neighX] = 1;
                pushMinHeap(openSet, &neigh);
            }
        }
    }

    for (int i = 0; i < field->height; i++) {
        free(closedSet[i]);
        free(openSetForPrint[i]);
        free(gMatrix[i]);
    }
    free(closedSet);
    free(openSetForPrint);
    free(gMatrix);

    for (int i = 0; i < dotsCount; i++) {
        free(allDots[i]);
    }
    free(allDots);
}

void freeField(Field *field) {
    for (int i = 0; i < field->height; i++) {
        free(field->wallData[i]);
    }
    free(field->wallData);
    free(field);
}

void cleanup(int sig) {
    system("clear");
    printf("Succesfully complete!\n");
    exit(0);
}

void runAStar() {
    winsize win{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

    int h = win.ws_row - 1;
    int w = win.ws_col / 2;
    Field *field = initField(h, w);

    signal(SIGINT, cleanup);
    signal(SIGTSTP, cleanup);

    while (true) {
        system("clear");
        randomizeWalls(field);
        loopPathFind(field, 0, 0, w-1, h-1);
    }
}