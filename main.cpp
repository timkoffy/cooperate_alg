#include "timkoffy/hashmap_linkedlist.h"

using namespace MyHashMapLinkedList;

int main() {
    HashMap *hm = createHashMap(5);

    addToHashMap(hm, "vova", 0);
    addToHashMap(hm, "petya", 1);
    addToHashMap(hm, "masha", 2);
    addToHashMap(hm, "dima", 3);
    addToHashMap(hm, "olya", 4);
    addToHashMap(hm, "sasha", 5);
    addToHashMap(hm, "katya", 6);
    addToHashMap(hm, "igor", 7);
    addToHashMap(hm, "anna", 8);




    printHashMap(hm);


    freeHashMap(hm);

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
