#pragma once

#include "../helper.h"

// RLE сжатие строк состоящих из букв. "AAAAABBC" -> "5A2B1C"
namespace Rle {
    char* encode(char* str) {
        char* res = (char*)malloc(100 * sizeof(char));
        int write = 0;
        int read = 0;
        while (str[read] != '\0') {
            char cur = str[read];
            // проверка на !цифру
            int count = 1;
            while (str[read + count] == cur) {
                count++;
            }
            read += count;

            int copy = count;
            int pow = 1;
            copy /= 10;
            while (copy > 0) {
                pow *= 10;
                copy /= 10;
            }

            while (pow > 0) {
                res[write++] = count / pow % 10 + '0';
                pow /= 10;
            }
            res[write++] = cur;
        }
        res[write] = '\0';
        return res;
    }

    char* decode(char* str) {
        char* res = (char*)malloc(100 * sizeof(char));
        int write = 0;
        int read = 0;

        while (str[read] != '\0') {
            int count = 0;
            while (Helper::isDigit(str[read]) ) {
                count = count * 10 + (str[read] - '0');
                read++;
            }

            for (int i = 0; i < count; i++) {
                res[write++] = str[read];
            }
            read++;
        }
        return res;
    }
}