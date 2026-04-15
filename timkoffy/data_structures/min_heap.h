#pragma once
#include <cstdlib>
#include <cstring>

namespace MyMinHeap {
    typedef struct {
        void *data;
        int sizeVar;
        int count;
        int capacity;
        int (*compare)(void *a, void *b);
    } MinHeap;

    MinHeap *initMinHeap(int sizeVar) {
        MinHeap *mh = (MinHeap*)malloc(sizeof(MinHeap));

        int capacity = 10;
        mh->data = malloc(sizeVar * capacity);
        mh->sizeVar = sizeVar;
        mh->count = 0;
        mh->capacity = capacity;

        return mh;
    }

    void swap(MinHeap *mh, int i, int j) {

    }

    int pushMinHeap(MinHeap *mh, void *src) {
        if (mh == nullptr) return 0;

        if (mh->count + 1 > mh->capacity) {
            int newCapacity = mh->capacity * 2;
            mh->data = realloc(mh->data, mh->sizeVar * newCapacity);
            if (mh->data == nullptr) {
                return 0;
            }
            mh->capacity = newCapacity;
        }

        // если родитель больше по значению, то свапаем. делаем пока не выполнится условие / не дойдем до корня.
        // свап происходит так: если нужно спавнуть родителя и левого, то получаем индекс родителя через (i - 1)/2 и спаваем по индексам

        memcpy((char*)mh->data + mh->count, src, mh->sizeVar);

        int curIndex = mh->count;
        while (curIndex > 0) {
            int parentIndex = (curIndex - 1) / 2;
            if (mh->compare((char*)mh->data + curIndex, (char*)mh->data + parentIndex)) { // если текущее меньше родителя
                swap(mh, curIndex, parentIndex);
                curIndex = parentIndex;
            }
        }

        mh->count++;
        return 1;
    }

    int popMinHeap(MinHeap *mh, void *dest) {
        if (mh == nullptr) return 0;

        if (mh->count + 1 < mh->capacity / 2 && mh->capacity > 10) {
            int newCapacity = mh->capacity / 2;
            mh->data = realloc(mh->data, mh->sizeVar * newCapacity);
            if (mh->data == nullptr) {
                return 0;
            }
            mh->capacity = newCapacity;
        }

        //

        return 1;
    }

    void freeMinHeap(MinHeap *mh) {
        free(mh->data);
        free(mh);
    }
}
