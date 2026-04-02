#pragma once
#include <cstdlib>

#include "../helper.h"

namespace MyBloomFilter {
    typedef struct {
        unsigned char *byteArray;
        int sizeBit;
        int sizeByte;
    } BloomFilter;

    void setBit(BloomFilter *bf, int index) {
        int byteIndex = index / 8;
        int bitIndex = index % 8;
        bf->byteArray[byteIndex] |= (1 << bitIndex);
    }

    int getBit(BloomFilter *bf, int index) {
        int byteIndex = index / 8;
        int bitIndex = index % 8;
        return (bf->byteArray[byteIndex] >> bitIndex) & 1;
    }

    BloomFilter *createBloomFilter(int sizeBit) {
        BloomFilter *bf = (BloomFilter*)malloc(sizeof(BloomFilter));
        if (bf == nullptr) return nullptr;
        bf->sizeBit = sizeBit;
        // 10 + 7 / 8 = 2
        // 15 + 7 / 8 = 2
        // 16 + 7 / 8 = 2
        // 17 + 7 / 8 = 3
        bf->sizeByte = (sizeBit + 7) / 8;
        bf->byteArray = (unsigned char*)calloc(bf->sizeByte, sizeof(unsigned char));
        if (bf->byteArray == nullptr) {
            free(bf);
            return nullptr;
        }
        return bf;
    }

    void addToBloomFilter(BloomFilter *bf, char *key) {
        unsigned int hash1 = Helper::hashCodeFirst(key, 5381);
        unsigned int hash2 = Helper::hashCodeFirst(key, 5381 + 101);
        unsigned int hash3 = Helper::hashCodeFirst(key, 5381 + 203);

        int index1 = hash1 % bf->sizeBit;
        int index2 = hash2 % bf->sizeBit;
        int index3 = hash3 % bf->sizeBit;

        setBit(bf, index1);
        setBit(bf, index2);
        setBit(bf, index3);
    }

    int containsBloomFilter(BloomFilter *bf, char *key) {
        unsigned int hash1 = Helper::hashCodeFirst(key, 5381);
        unsigned int hash2 = Helper::hashCodeFirst(key, 5381 + 101);
        unsigned int hash3 = Helper::hashCodeFirst(key, 5381 + 203);

        int index1 = hash1 % bf->sizeBit;
        int index2 = hash2 % bf->sizeBit;
        int index3 = hash3 % bf->sizeBit;

        if (!getBit(bf, index1)) return 0;
        if (!getBit(bf, index2)) return 0;
        if (!getBit(bf, index3)) return 0;

        return 1;
    }

    void freeBloomFilter(BloomFilter *bf) {
        if (bf != nullptr) {
            free(bf->byteArray);
            free(bf);
        }
    }
}
