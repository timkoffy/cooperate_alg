#include "timkoffy/hashmap_linkedlist.h"

#include "timkoffy/bloomFilter.h"

using namespace MyBloomFilter;

int main() {
    BloomFilter *bf = createBloomFilter(1000);  // 1000 бит

    addToBloomFilter(bf, "vova");
    addToBloomFilter(bf, "petya");
    addToBloomFilter(bf, "masha");

    printf("vova: %d\n", containsBloomFilter(bf, "vova"));
    printf("dima: %d\n", containsBloomFilter(bf, "dima"));

    freeBloomFilter(bf);
    return 0;



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
