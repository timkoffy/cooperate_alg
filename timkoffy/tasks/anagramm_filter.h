#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <vector>

// суть : пока заполняем хешмапы для каждой строки ищем hash
// (в данном случае сумма всех кодов символов).
// если хеш/длина не совпадают - сразу шкип
// если совпадают то проходим по хешмапе

namespace AnagramFilter {
    // // Array
    //
    // typedef struct {
    //     void *data;
    //     int sizeVar;
    //     int count;
    //     int capacity;
    // } Array;
    //
    // Array *initArray(int sizeVar, int capacity) {
    //     Array *arr = (Array*)malloc(sizeof(Array));
    //     arr->sizeVar = sizeVar;
    //     arr->capacity = capacity;
    //     arr->data = malloc(arr->sizeVar * arr->capacity);
    //     arr->count = 0;
    //
    //     return arr;
    // }
    //
    // void pushArray(Array *arr, void *src) {
    //     if (arr->count + 1 > arr->capacity) {
    //         int newCapacity = arr->capacity * 2;
    //         void *newData = realloc(arr->data, newCapacity * arr->sizeVar);
    //         if (newData == nullptr) {
    //             return;
    //         }
    //         arr->capacity = newCapacity;
    //         arr->data = newData;
    //     }
    //
    //     memcpy((char*)arr->data + arr->count, src, arr->sizeVar);
    //
    //     arr->count++;
    // }
    //
    // void insertArray(Array *arr, void *src, int index) {
    //     if (index < 0 || index > arr->count) {
    //         return;
    //     }
    //
    //     if (arr->count + 1 > arr->capacity) {
    //         int newCapacity = arr->capacity * 2;
    //         void *newData = realloc(arr->data, newCapacity * arr->sizeVar);
    //         if (newData == nullptr) {
    //             return;
    //         }
    //         arr->capacity = newCapacity;
    //         arr->data = newData;
    //     }
    //
    //     // [0, 1, 2, 3] count = 4
    //     // index = 2
    //     // [0, 1, &, 2, 3]
    //
    //     // [0] count = 1
    //
    //     // index = 0;
    //     // [&, 0]
    //
    //     // index = 1;
    //     // [0, &]
    //
    //
    //     for (int i = arr->count; i > index; i--) {
    //         void *destTmp = (char*)arr->data + i;
    //         void *srcTmp = (char*)arr->data + i - 1;
    //         memcpy(destTmp, srcTmp, arr->sizeVar);
    //     }
    //
    //     memcpy((char*)arr->data + index, src, arr->sizeVar);
    //
    //     arr->count++;
    // }
    //
    // // HashMap
    //
    // typedef struct {
    //     Array *buckets;
    //     int countElements;
    // } HashMap;
    //
    // HashMap *initHashMap() {
    //     HashMap *hm = (HashMap*)malloc(sizeof(HashMap));
    //     hm->buckets = nullptr;
    //     hm->countElements = 0;
    //     return hm;
    // }
    //
    // void pushHashMapChar(HashMap *hm, char key, int value) {
    //     if (hm->buckets == nullptr) {
    //         hm->buckets = initArray(sizeof(Array*), 1);
    //         Array *bucket = initArray(sizeof(int), 1);
    //         pushArray(hm->buckets, &bucket);
    //     }
    //     // cat
    //     // [] countElements = 0 countBuckets = 0
    //     // c = 2 -> [[c](1)] countElements = 1 countBuckets = 1
    //
    //     // [[c](1)] countElements = 1 countBuckets = 1
    //     // ++bucket: countElements = 1 countBuckets = 2
    //     // c = 2, 2 % 2 = 0
    //     // a = 0 ->[[c, a](2), [](0)] countElements = 2 countBuckets = 2
    //
    //     if (hm->countElements + 1 > hm->buckets->count) {
    //         Array *newBuckets = initArray(sizeof(Array*), hm->buckets->count * 2);
    //         for (int i = 0; i < hm->buckets->count; i++) {
    //             Array *newBucket = initArray(sizeof(int), 1);
    //             pushArray(newBuckets, &newBucket);
    //         }
    //     }
    //
    //     int hashIndex = key % (hm->buckets->count + 1);
    //     insertArray(hm->buckets, &value, hashIndex);
    // }
    //
    // int hashCode(const char *str, int *len) {
    //     int res = 0;
    //     int i = 0;
    //     // "abc\0"
    //     while (str[i] != '\0') {
    //         res += (int)toLower(str[i++]) * 1548;
    //     }
    //     *len = i;
    //     return res;
    // }









    // task yo

    char toLower(char ch) {
        if (ch >= 'A' && ch <= 'Z') {
            return ch + ('a' - 'A');
        }
        return ch;
    }

    char ***findAnagrams(char **allStr, int strCount, int* groupCount, int** groupLengths) {
        int *hashes = (int*)malloc(sizeof(int) * strCount);
        int *lengths = (int*)malloc(sizeof(int) * strCount);
        int *checked = (int*)calloc(strCount, sizeof(int));
        std::vector<std::unordered_map<char, int>> maps(strCount);

        // заполняем массивы
        for (int i = 0; i < strCount; i++) {
            int hash = 0;
            int j = 0;
            std::unordered_map<char, int> map;

            while (allStr[i][j] != '\0') {
                char ch = toLower(allStr[i][j]);
                hash += ch * 1548;
                map[ch]++;
                j++;
            }

            hashes[i] = hash;
            lengths[i] = j;
            maps[i] = map;
        }

        // инициализация финального массива групп анаграмм
        char*** res = (char***)malloc(sizeof(char**) * strCount);
        *groupLengths = (int*)malloc(sizeof(int) * strCount);
        *groupCount = 0;

        // проверка всех строк
        for (int strIndex = 0; strIndex < strCount; strIndex++) {
            if (checked[strIndex]) continue;

            int anagramCapacity = 10;
            char **anagramGroup = (char**)malloc(anagramCapacity * sizeof(char*));
            anagramGroup[0] = allStr[strIndex];
            int anagramCount = 1;

            // проверка всех следующих строк после текущей
            for (int cmpStrIndex = strIndex + 1; cmpStrIndex < strCount; cmpStrIndex++) {
                // шкип всего что очевидно не подходит
                if (checked[cmpStrIndex]) continue;
                if (hashes[strIndex] != hashes[cmpStrIndex]) continue;
                if (lengths[strIndex] != lengths[cmpStrIndex]) continue;

                // проверка на анаграмму
                int equal = 1;
                for (int curCharIndex = 0; allStr[strIndex][curCharIndex] != '\0'; curCharIndex++) {
                    char ch = toLower( allStr[strIndex][curCharIndex] );
                    if (maps[strIndex][ch] != maps[cmpStrIndex][ch]) {
                        equal = 0;
                        break;
                    }
                }

                // добавляем строку в текущую группу
                if (equal) {
                    checked[cmpStrIndex] = 1;
                    if (anagramCount + 1 > anagramCapacity) {
                        anagramCapacity *= 2;
                        anagramGroup = (char**)realloc(anagramGroup, anagramCapacity * sizeof(char*));
                    }
                    anagramGroup[anagramCount++] = allStr[cmpStrIndex];
                }
            }

            // сохраняем группу
            (*groupLengths)[*groupCount] = anagramCount;

            anagramGroup = (char**)realloc(anagramGroup, anagramCount * sizeof(char*));
            res[*groupCount] = anagramGroup;

            (*groupCount)++;

            checked[strIndex] = 1;
        }

        res = (char***)realloc(res, (*groupCount) * sizeof(char**));
        *groupLengths = (int*)realloc(*groupLengths, (*groupCount) * sizeof(int));

        free(hashes);
        free(lengths);
        free(checked);

        return res;
    }

    void freeRes(char*** res, int groupCount, int* groupLengths) {
        for (int i = 0; i < groupCount; i++) {
            free(res[i]);
        }
        free(res);
        free(groupLengths);
    }

    void run() {
        int strCount = 6;
        char **allStr = (char**)malloc(sizeof(char*) * strCount);
        allStr[0] = strdup("Eat");
        allStr[1] = strdup("tEA");
        allStr[2] = strdup("tan");
        allStr[3] = strdup("ate");
        allStr[4] = strdup("nat");
        allStr[5] = strdup("bat");

        for (int i = 0; i < strCount; i++) {
            printf("%s", allStr[i]);
            if (i < strCount - 1) printf(", ");
        } printf("\n\n");

        int groupCount;
        int* groupLengths;
        char*** res = findAnagrams(allStr, strCount, &groupCount, &groupLengths);

        for (int i = 0; i < groupCount; i++) {
            printf("%d) ", i + 1);
            for (int j = 0; j < groupLengths[i]; j++) {
                printf("%s", res[i][j]);
                if (j < groupLengths[i] - 1) printf(", ");
            } printf("\n");
        }

        for (int i = 0; i < strCount; i++) {
            free(allStr[i]);
        }
        free(allStr);
        freeRes(res, groupCount, groupLengths);
    }
}
