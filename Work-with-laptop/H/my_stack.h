#pragma once
#include <iostream>
#include <cstring>

namespace MyStack {
    typedef struct {
        void* first;
        int capacity;
        int count;
        int size_el;
    } Stack;

    Stack* createStack(int cap, int size_el) {
        if (cap <= 0) return NULL;

        Stack* stack = (Stack*)malloc(sizeof(Stack));
        if (stack == NULL) return NULL;

        void* array = malloc(size_el * cap);
        if (array == NULL) {
            free(stack);
            return NULL;
        }

        stack->first = array;
        stack->capacity = cap;
        stack->count = 0;
        stack->size_el = size_el;

        return stack;
    }

    void pushStack(Stack* stack, void* value) {
        if (stack->count + 1 > stack->capacity) {
            stack->capacity = 2 * stack->capacity + 1;
            stack->first = realloc(stack->first, stack->size_el * stack->capacity);
        }

        memcpy((char*)stack->first + stack->count * stack->size_el, value, stack->size_el);
        stack->count++;
    }

    int peekStack(Stack* stack, void* out) {
        if (stack == NULL  || stack->count == 0) return 0;

        memcpy(out, (char*)stack->first + (stack->count - 1) * stack->size_el, stack->size_el);
        return 1;
    }

    int popStack(Stack* stack, void* out) {
        int ok = peekStack(stack, out);
        if (!ok) return 0;

        if (stack->count - 1 < stack->capacity / 2) {
            stack->capacity = stack->capacity / 2 + 1;
            stack->first = realloc(stack->first, stack->size_el * stack->capacity);
        }

        stack->count--;
        return 1;
    }

    int lenStack(Stack* stack) {
        return stack->count;
    }

    void freeStack(Stack* stack) {
        if (stack) {
            if (stack->first) {
                free(stack->first);
            }
            free(stack);
        }
    }
}
