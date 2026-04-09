#pragma once
#include <vector>

class LRUCache {
public:
    LRUCache(int capacity) {
        capacity_m = capacity;
        count_m = 0;
        data.resize(capacity);
    }

    int get(int key) {
        print();
        int i = 0;
        while (i < count_m) {
            if (data.at(i).first == key) {
                update(i);
                printf("- [%d, %d] at %d\n", data.at(0).first, data.at(0).second, i);
                return data.at(0).second;
            }
            i++;
        }
        printf("- [%d, ?] at ? (not found)\n", key);
        return -1;
    }

    void put(int key, int value) {
        print();
        count_m += count_m < capacity_m ? 1 : 0;
        int i = 0;
        while (i < count_m) {
            if (data.at(i).first == key) {
                break;
            }
            i++;
        }
        update(i);
        printf("+ [%d, %d] at %d\n", key, value, 0);
        data.at(0) = {key, value};
    }

    void print() {
        for (int i = 0; i < capacity_m; i++) {
            if (i < count_m) {
                printf("[%d, %d] ", data.at(i).first, data.at(i).second);
                continue;
            }
            printf("[?, ?] ");
        }
        printf("\n\n");
    }
private:
    void update(int i) {
        auto tmp = data.at(i);
        int j = i;
        while(j > 0) {
            if (j >= capacity_m) continue;
            data.at(j) = data.at(j - 1);
            j--;
        }
        data.at(0) = tmp;
    }

    int capacity_m;
    int count_m;
    std::vector<std::pair<int, int>> data;
};
