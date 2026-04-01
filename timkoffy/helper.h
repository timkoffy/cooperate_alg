#pragma once
#include <chrono>
#include <iostream>

namespace Helper {
    class Timer {
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
    public:
        Timer() : start(std::chrono::high_resolution_clock::now()) {}
        ~Timer() {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << " [" << duration.count() << " ms]\n";
        }
    };

    int isDigit(char c) {
        if (c >= '0' && c <= '9')
            return 1;
        return 0;
    }

    int cmpStr(char *first, char *second) {
        int i = 0;
        int equal = 1;
        while (first[i] != '\0' || second[i] != '\0') {
            if (first[i] != second[i]) {
                equal = 0;
                break;
            }
            i++;
        }
        return equal;
    }

    unsigned int hashCodeFirst(char *str, unsigned int seed) {
        unsigned int hash = seed;
        int i = 0;
        while (str[i] != '\0') {
            hash = (hash << 5) + hash + (unsigned int)(str[i]);
            i++;
        }
        return hash;
    }

    unsigned int hashCodeFirst(char *str) {
        return hashCodeFirst(str, 5381);
    }

    void printArrayInt(int *array, int size, char *name) {
        if (array == nullptr || size < 1) return;

        printf("%s: ", name);
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }
}
