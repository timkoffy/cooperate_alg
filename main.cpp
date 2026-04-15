// реаллок файл подкачки(перезапись)

#include "timkoffy/data_structures/graph_adjmatrix.h"
// #include "timkoffy/data_structures/LRUCache.h"
#include "timkoffy/tasks/render_graph.h"

// массив целых полож чисел. найти треугольник, который обладает наибольшим периметром

// из всех палочек необходимо получить все возможные вариации треугольника включая все вариации треугольников
// каждая палочка уникальна


int main() {
    Graph *g = createGraph(7);

    tryAddUnorderedEdge(g, 0, 1);
    tryAddUnorderedEdge(g, 0, 2);
    tryAddUnorderedEdge(g, 1, 2);
    tryAddUnorderedEdge(g, 1, 3);
    tryAddUnorderedEdge(g, 3, 4);
    tryAddUnorderedEdge(g, 4, 5);
    tryAddUnorderedEdge(g, 5, 6);
    tryAddUnorderedEdge(g, 6, 0);

    printGraph(g);

    removeAllCycles(g);

    printGraph(g);

    renderGraph(g);

    // auto lRUCache = LRU::LRUCache(2);
    // lRUCache.put(1, 1); // cache is {1=1}
    // lRUCache.put(2, 2); // cache is {1=1, 2=2}
    // lRUCache.get(1);    // return 1
    // lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    // lRUCache.get(2);    // returns -1 (not found)
    // lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    // lRUCache.get(1);    // return -1 (not found)
    // lRUCache.get(3);    // return 3
    // lRUCache.get(4);    // return 4
    // lRUCache.print();
}