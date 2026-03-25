#include "timkoffy/hashmap_linkedlist.h"

#include "timkoffy/bloomFilter.h"

#include <unordered_map>

using namespace MyBloomFilter;

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

std::unordered_map<char*, int> countUniqueSubstrings(char *str) {
    std::unordered_map<char*, int> map;
    int i = 0;
    while (str[i] != '\0') {
        int j = 0;
        while (str[i + j] != '\0') {
            char *substr = substring(str, i, i + j);
            map[substr] = 1;
            j++;
        }
        i++;
    }
    return map;
}

int main() {
    char *str = "abab";
    auto map = countUniqueSubstrings(str);
    for (auto [key, value] : map) {
        printf("%s\n", key);
    }

    // HashMap *hm = createHashMap(5);
    //
    // addToHashMap(hm, "vova", 0);
    // addToHashMap(hm, "petya", 1);
    // addToHashMap(hm, "masha", 2);
    // addToHashMap(hm, "dima", 3);
    // addToHashMap(hm, "olga", 4);
    // addToHashMap(hm, "sasha", 5);
    // addToHashMap(hm, "katya", 6);
    // addToHashMap(hm, "igor", 7);
    // addToHashMap(hm, "anna", 8);
    // addToHashMap(hm, "nastya", 9);
    // addToHashMap(hm, "vofdva", 10);
    //
    // printf("%d\n", containsKey(hm, "vofdva"));
    //
    // printHashMap(hm);
    //
    // printf("\n");
    // tryRemoveFromHashMap(hm, "masha");
    //
    // printHashMap(hm);
    //
    // freeHashMap(hm);



    // Graph *g = createGraph(6);
    //
    // tryAddUndirectedEdge(g, 0, 1, 0);
    // tryAddUndirectedEdge(g, 1, 2, 0);
    // tryAddUndirectedEdge(g, 2, 3, 0);
    // tryAddUndirectedEdge(g, 3, 0, 0);
    // tryAddUndirectedEdge(g, 1, 5, 0);
    // tryAddUndirectedEdge(g, 1, 4, 0);
    // tryAddUndirectedEdge(g, 5, 4, 0);
    //
    // printGraph(g);
    //
    // printf("\n");
    //
    // Array *path = MyEulerPath::EulerHirHolzer(g, 0);
    // for (int i = 0; i < path->size; i++) {
    //     printf("%d ", path->data[i]);
    // }
    //
    // freeArray(path);
    //
    // freeGraph(g);
}
