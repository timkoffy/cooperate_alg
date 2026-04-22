#pragma once

#include <cstdio>
#include <cstdlib>

void clearFlags(char *exists, char *str, int i, int j) {
    for (int k = i; k <= j; k++) {
        char ch = str[k];
        exists[(int)ch] = 0;
    }
}

void printSubstr(char *str, int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

void printExists(char *exists) {
    for (int i = 'a'; i < 'z'; i++) {
        printf("%c ", i);
    }
    printf("\n");
    for (int i = 'a'; i < 'z'; i++) {
        printf("%i ", exists[i]);
    }
    printf("\n");
}

int getUniquePattern(char *str) {
    char *exists = (char*)calloc(256, sizeof(char));

    int maxLen = 0;
    int left = 0;
    for (int right = 0; str[right] != '\0'; right++) {
        char rightChar = str[right];
        while (exists[rightChar] == 1 && left < right) {
            char leftChar = str[left];
            exists[leftChar] = 0;
            left++;
        }

        exists[(int)rightChar] = 1;

        int subLen = right - left + 1;
        maxLen = maxLen < subLen ? subLen : maxLen;
        printSubstr(str, left, right);
    }

    free(exists);
    return maxLen;
}