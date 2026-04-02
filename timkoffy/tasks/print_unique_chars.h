#pragma once

#include <cstdio>
#include <unordered_map>

// вывести все уникальные символы в строке(которые встречаются один раз на всю строку)
void printUniqueChars(char *str) {
    std::unordered_map<char, int> chars;
    int i = 0;
    while (str[i] != '\0') {
        if (!chars.contains(str[i])) {
            chars.emplace(str[i], 1);
        } else {
            chars.at(str[i])++;
        }
        i++;
    }

    for (auto [ch, n] : chars) {
        if (n == 1) printf("%c\n", ch);
    }
}