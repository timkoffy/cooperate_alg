#pragma once
#include <cstdlib>
#include "../data_structures/hashmap.h"

using namespace MyHashMapLinkedList;

namespace taskCountSubstringsWithHashMap {
    // поиск колва уникальных подстрок в строке с использованием std::map; 1+ символ
    char *substring(char *str, int start, int end) {
        char *substr = (char*)malloc(end - start + 1);
        int i = 0;
        while (start + i < end + 1 && str[start + i] != '\0') {
            substr[i] = str[start + i];
            i++;
        }
        substr[i] = '\0';
        return substr;
    }

    int countUniqueSubstrings(char *str) {
        HashMap *map = createHashMap(5);
        int i = 0;
        while (str[i] != '\0') {
            int j = 0;
            while (str[i + j] != '\0') {
                char *substr = substring(str, i, i + j);
                addToHashMap(map, substr, 1);
                j++;
            }
            i++;
        }
        int count = map->count;
        freeHashMap(map);
        return count;
    }
}