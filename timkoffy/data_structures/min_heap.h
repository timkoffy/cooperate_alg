#pragma once

#include <cstring>

namespace MyMinHeap {
    typedef struct {
        void *data;
        int sizeVar;
        int count;
        int capacity;
        int (*compare)(const void *a, const void *b);
    } MinHeap;

    MinHeap *initMinHeap(int sizeVar, int (*compare)(const void *a, const void *b)) {
        MinHeap *mh = (MinHeap*)malloc(sizeof(MinHeap));

        int capacity = 10;
        mh->data = malloc(sizeVar * capacity);
        mh->sizeVar = sizeVar;
        mh->count = 0;
        mh->capacity = capacity;
        mh->compare = compare;

        return mh;
    }

    void swap(MinHeap *mh, int i, int j) {
        void *tmp = malloc(mh->sizeVar);

        memcpy(tmp, (char*)mh->data + i * mh->sizeVar, mh->sizeVar);
        memcpy((char*)mh->data + i * mh->sizeVar, (char*)mh->data + j * mh->sizeVar, mh->sizeVar);
        memcpy((char*)mh->data + j * mh->sizeVar, tmp, mh->sizeVar);

        free(tmp);
    }

    int pushMinHeap(MinHeap *mh, void *src) {
        if (mh == nullptr) return 0;

        if (mh->count + 1 > mh->capacity) {
            int newCapacity = mh->capacity * 2;
            void *newData = realloc(mh->data, mh->sizeVar * newCapacity);
            if (newData == nullptr) {
                return 0;
            }
            mh->data = newData;
            mh->capacity = newCapacity;
        }

        // если родитель больше по значению, то свапаем. делаем пока не выполнится условие / не дойдем до корня.
        // свап происходит так: если нужно спавнуть родителя и ребенка, то получаем индекс родителя через (i - 1)/2 и спаваем по индексам

        int curIndex = mh->count;
        memcpy((char*)mh->data + curIndex * mh->sizeVar, src, mh->sizeVar);
        mh->count++;

        while (curIndex > 0) {
            int parentIndex = (curIndex - 1) / 2;
            if (mh->compare((char*)mh->data + curIndex * mh->sizeVar,
                            (char*)mh->data + parentIndex * mh->sizeVar) < 0) { // если текущее меньше родителя
                swap(mh, curIndex, parentIndex);
                curIndex = parentIndex;
            } else {
                break;
            }
        }

        return 1;
    }

    int popMinHeap(MinHeap *mh, void *dest) {
        if (mh == nullptr || mh->count <= 0) return 0;

        // свап корня с последним элементов, удаляем корень(выводим в результат)
        // проходим сверху вниз и проверяем что родитель меньше чем дети

        memcpy(dest, mh->data, mh->sizeVar);

        // 0 1 2 3 4: 5
        mh->count--;
        // 0 1 2 3 4: 4
        memcpy(mh->data, (char*)mh->data + mh->count * mh->sizeVar, mh->sizeVar);
        // 4 1 2 3 4: 4
        int curIndex = 0;
        while (1) {
            int leftChild = (curIndex * 2) + 1;
            int rightChild = (curIndex * 2) + 2;
            int smallest = curIndex;
            if (leftChild < mh->count &&
                mh->compare((char*)mh->data + leftChild * mh->sizeVar,
                            (char*)mh->data + smallest * mh->sizeVar) < 0) {
                smallest = leftChild;
            }

            if (rightChild < mh->count &&
                mh->compare((char*)mh->data + rightChild * mh->sizeVar,
                            (char*)mh->data + smallest * mh->sizeVar) < 0) {
                smallest = rightChild;
            }

            if (smallest == curIndex) break;

            swap(mh, curIndex, smallest);
            curIndex = smallest;
        }

        return 1;
    }

    void freeMinHeap(MinHeap *mh) {
        free(mh->data);
        free(mh);
    }
}
