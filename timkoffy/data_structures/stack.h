#pragma once
#include <iostream>
#include <cstring>

namespace MyStack {
    typedef struct {
        void* first;
        int capacity;
        int count;
        int sizeVar;
    } Stack;

    Stack* createStack(int cap, int sizeVar) {
        if (cap <= 0) return nullptr;

        Stack* s = (Stack*)malloc(sizeof(Stack));
        if (s == nullptr) return nullptr;

        void* array = malloc(sizeVar * cap);
        if (array == nullptr) {
            free(s);
            return nullptr;
        }

        s->first = array;
        s->capacity = cap;
        s->count = 0;
        s->sizeVar = sizeVar;

        return s;
    }

    void pushStack(Stack* s, void* value) {
        if (s->count + 1 > s->capacity) {
            s->capacity = 2 * s->capacity + 1;
            s->first = realloc(s->first, s->sizeVar * s->capacity);
        }

        memcpy((char*)s->first + s->count * s->sizeVar, value, s->sizeVar);
        s->count++;
    }

    int peekStack(Stack* s, void* out) {
        if (s == nullptr  || s->count == 0) return 0;

        memcpy(out, (char*)s->first + (s->count - 1) * s->sizeVar, s->sizeVar);
        return 1;
    }

    int popStack(Stack* s, void* out) {
        int ok = peekStack(s, out);
        if (!ok) return 0;

        if (s->count - 1 < s->capacity / 2) {
            s->capacity = s->capacity / 2 + 1;
            s->first = realloc(s->first, s->sizeVar * s->capacity);
        }

        s->count--;
        return 1;
    }

    int editTopStack(Stack* s, int offset, int sizeLocalVar, void* value) {
        if (s == nullptr  || s->count == 0) return 0;

        memcpy((char*)s->first + (s->count - 1) * s->sizeVar + offset, value, sizeLocalVar);
        return 1;
    }

    void freeStack(Stack* stack) {
        if (stack) {
            if (stack->first) {
                free(stack->first);
            }
            free(stack);
        }
    }

    void printStackInt(Stack* s) {
        printf("stack: ");
        for (int i = 0; i < s->count; i++) {
            printf("%d ", ((int*)s->first)[i]);
        }
        printf("\n");
    }
}