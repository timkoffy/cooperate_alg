#pragma once

namespace LRU {
    class Item {
    public:
        Item(int value) : value_m(value), next_m(nullptr) {}

        int value_m;
        Item *next_m;
    };

    class Queue {
    public:
        Queue() : first_m(nullptr), last_m(nullptr) {}

        ~Queue() {
            Item *ptr = first_m;
            while (ptr != nullptr) {
                Item *next = ptr->next_m;
                delete ptr;
                ptr = next;
            }
        }

        void push(int value) {
            Item *item = new Item(value);

            if (first_m == nullptr) {
                first_m = last_m = item;
                return;
            }
            last_m->next_m = item;
            last_m = item;
        }

        int pop() {
            if (first_m == nullptr) return -1;

            int value = first_m->value_m;
            Item *tmp = first_m;
            first_m = first_m->next_m;

            if (first_m == nullptr) {
                last_m = nullptr;
            }

            delete tmp;
            return value;
        }

        void print() {
            Item *ptr = first_m;
            while (ptr != nullptr) {
                printf("%d ", ptr->value_m);
                ptr = ptr->next_m;
            }
            printf("\n");
        }

    private:
        Item *first_m;
        Item *last_m;
    };

    class LRUCache {
    public:
        LRUCache(int capacity) {
            capacity_m = capacity;
            count_m = 0;
            data.resize(capacity);
        }

        int get(int key) {
            bool exist = false;
            int i = 0;
            while (i < count_m) {
                if (data.at(i).first == key) {
                    auto tmp = data.at(i);
                    shift(i);
                    data.at(0) = tmp;
                    exist = true;
                    break;
                }
                i++;
            }
            return exist ? data.at(0).second : -1;
        }

        void put(int key, int value) {
            if (count_m < capacity_m) {
                int i = 0;
                while (i < count_m) {
                    if (data.at(i).first == key) {
                        shift(i);
                        break;
                    }
                    i++;
                }
                if (i == count_m) shift(i);
                data.at(0) = {key, value};
                count_m++;
                return;
            }

            int i = 0;
            while (i < capacity_m) {
                if (data.at(i).first == key) {
                    shift(i);
                    break;
                }
                i++;
            }
            if (i == capacity_m) shift(i - 1);
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
        void shift(int i) {
            // [0, 1, 2, 3] << 2
            // [0, 0, 1, 3]
            while (i > 0) {
                data.at(i) = data.at(i - 1);
                i--;
            }
        }
        int capacity_m;
        int count_m;
        std::vector<std::pair<int, int>> data;
    };
}