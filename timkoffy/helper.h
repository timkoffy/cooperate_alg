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
}
