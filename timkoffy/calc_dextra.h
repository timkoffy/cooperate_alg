#pragma once
#include <cstdio>

#include "helper.h"
#include "my_queue.h"
#include "my_stack.h"

using namespace MyQueue;
using namespace MyStack;

namespace CalcDextra {
    enum {
        DIGIT = 0,
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        OPEN,
        CLOSE,
        UNKNOWN
    };

    typedef struct {
        int type;
        double value;
    } Item;

    int convertOperator(char c) {
        switch (c) {
            case '+': return ADD;
            case '-': return SUB;
            case '*': return MUL;
            case '/': return DIV;
            case '%': return MOD;
            default: return UNKNOWN;
        }
    }

    int isOperator(int type) {
        if (type >= ADD && type <= MOD) return 1;
        return 0;
    }

    int isOperator(char c) {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') return 1;
        return 0;
    }

    int isGreaterOrSameByPriority(int type2, char c2) {
        int type1 = convertOperator(c2);

        int p1 = -1, p2 = 0;

        if(type1 == MUL || type1 == DIV || type1 == MOD)     p1 = 2;
        else if (type1 == ADD || type1 == SUB)               p1 = 1;

        if(type2 == MUL || type2 == DIV || type2 == MOD)     p2 = 2;
        else if (type2 == ADD || type2 == SUB)               p2 = 1;

        return p1 >= p2;
    }

    Queue* dextra(const char* expression) {
        if (expression == nullptr || expression[0] == '\0') return nullptr;

        Stack* s = createStack(10, sizeof(Item));
        Queue* result = createQueue(sizeof(Item));

        int i = 0;
        while (expression[i] != '\0') {
            if (Helper::isDigit(expression[i])) {
                double digit = 0;
                while (Helper::isDigit(expression[i])) {
                    digit = digit * 10 + (expression[i] - '0');
                    i++;
                }
                Item item = {DIGIT, digit};
                enqueue(result, &item);
                continue;
            }
            if (expression[i] == '(') {
                Item item{OPEN, 0};
                pushStack(s, &item);
            }
            else if (expression[i] == ')') {
                Item cur;
                popStack(s, &cur);
                while (cur.type != OPEN) {
                    enqueue(result, &cur);
                    if (!popStack(s, &cur)) {
                        freeQueue(result);
                        freeStack(s);
                        printf("invalid expression\n");
                        return nullptr;
                    }
                }
            }
            else if (isOperator(expression[i])) {
                Item newItem;
                newItem.value = 0;
                newItem.type = convertOperator(expression[i]);

                Item topItem;
                while (s->count > 0) {
                    peekStack(s, &topItem);
                    if (isOperator(topItem.type) && isGreaterOrSameByPriority(topItem.type, expression[i])) {
                        popStack(s, &topItem);
                        enqueue(result, &topItem);
                    } else break;
                }
                pushStack(s, &newItem);
            } i++;
        }
        while (s->count > 0) {
            Item item;
            popStack(s, &item);
            if (item.type == OPEN) {
                freeStack(s);
                freeQueue(result);
                printf("invalid expression\n");
                return nullptr;
            } enqueue(result, &item);
        } freeStack(s);
        return result;
    }

    double evaluate(const char* expressionInfl) {
        Queue* expression = dextra(expressionInfl);
        if (expression == nullptr) return 0;
        Stack* s = createStack(10, sizeof(Item));

        int i = 0;
        while (!isEmptyQueue(expression)) {
            Item cur;
            dequeue(expression, &cur);
            if (cur.type == DIGIT) {
                pushStack(s, &cur);
            }
            else if (isOperator(cur.type)) {
                Item first;
                if (!popStack(s, &first)) {
                    freeStack(s);
                    printf("invalid expression\n");
                    return 0;
                }
                Item second;
                if (!popStack(s, &second)) {
                    freeStack(s);
                    printf("invalid expression\n");
                    return 0;
                }

                Item result;
                result.type = 0;
                switch (cur.type) {
                    case ADD: result.value = second.value + first.value; break;
                    case SUB: result.value = second.value - first.value; break;
                    case MUL: result.value = second.value * first.value; break;
                    case DIV: result.value = second.value / first.value; break;
                    case MOD: result.value = (int)(second.value) % (int)(first.value); break;
                    default: printf("invalid expression"); return 0;
                } pushStack(s, &result);
            } i++;
        }
        Item result;
        popStack(s, &result);
        freeStack(s);
        freeQueue(expression);
        return result.value;
    }
}
