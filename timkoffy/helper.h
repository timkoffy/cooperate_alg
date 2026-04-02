#pragma once
#include <chrono>
#include <iostream>

namespace Helper {
    // таймер в миллисекундах. использование:
    // {
    //      Timer t;
    //      foo();
    // }
    // >> [0.029437 ms]
    //
    // !! важно: создавать объект Timer в отдельном скоупе
    //    вместе с функцией, при выходе из скоупа срабатвает
    //    деструктор и выводится время в ms.
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

    // проверка символа на цифру, возвращает 1 если цифра, 0 если нет
    int isDigit(char c) {
        if (c >= '0' && c <= '9')
            return 1;
        return 0;
    }

    // сравнение строк, возвращает 1 если равны, 0 если нет
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

    // хеш функция DJB2
    unsigned int hashCode(char *str, unsigned int seed) {
        unsigned int hash = seed;
        int i = 0;
        while (str[i] != '\0') {
            hash = (hash << 5) + hash + (unsigned int)(str[i]);
            i++;
        }
        return hash;
    }

    unsigned int hashCode(char *str) {
        return hashCode(str, 5381);
    }

    // вывод массива чисел, например:
    // digits: 1, 2, 3, 4, 5
    void printArrayInt(int *array, int size, char *name) {
        if (array == nullptr || size < 1) return;

        printf("%s: ", name);
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    // модуль
    double myAbs(double num) {
        return num >= 0 ? num : -num;
    }

    // степени положительная и отрицательная
    double myPow(double num, int pow) {
        if (pow < 0) return 0;
        if (pow == 0) return 1;
        double res = num;
        pow--;
        while (pow > 0) {
            if (res > res * num) printf("int overflow\n");
            res *= num;
            pow--;
        }
        return res;
    }

    double myNegativePow(double A, int n) {
        if (A <= 0 || n <= 0) return 0;
        printf("%lf\n", A);
        double x = A / n;
        int i = 0;
        while (myAbs(x * x - A) > 0.000001) {
            x = ( (A / myPow(x, n - 1)) + ((n - 1) * x) ) / n;
            i++;
            if (i > 20) return x;
            // printf("%lf\n", x);
        }
        return x;
    }
}
