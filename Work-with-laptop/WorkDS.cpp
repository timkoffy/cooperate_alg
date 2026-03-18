#include <iostream>
#include <cstring>

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

int peek(Stack* stack, void* out) {
    if (stack == NULL  || stack->count == 0) return 0;

    memcpy(out, (char*)stack->first + (stack->count - 1) * stack->size_el, stack->size_el);
    return 1;
}

int popStack(Stack* stack, void* out) {
    int ok = peek(stack, out);
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

// считун из обратной польской
int isDigit(char c) {
    if (c >= '0' && c <= '9') return 1;
    return 0;
}

int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') return 1;
    return 0;
}

int isGreaterOrSameByPriority(char c, char c1) {
    int p1, p2;

    if(c == '*' || c == '/' || c == '%'){
        p1 = 2;
    }
    else if(c == '+' || c == '-'){
        p1 = 1;
    }

    if(c1 == '*' || c1 == '/' || c1 == '%'){
        p2 = 2;
    }
    else if(c1 == '+' || c1 == '-'){
        p2 = 1;
    }

    return p1>=p2;
}

char* dextra(char* expression) {
    if (expression == nullptr || expression[0] == '\0') return nullptr;

    int size = 1;

    char* result = (char*)malloc(size);

    Stack* s = createStack(10, sizeof(char));

    int i = 0;
    int write = 0;
    while (expression[i] != '\0') {
        if (isDigit(expression[i])) {
            result[write++] = expression[i];
            result = (char*)realloc(result,size++);
        }
        else if (expression[i] == '(') {
            pushStack(s, &expression[i]);
        }
        else if (expression[i] == ')') {
            char cur;
            popStack(s, &cur);
            while (cur != '(') {
                result[write++] = cur;
                popStack(s, &cur);
            }
        }
        else if (isOperator(expression[i])) {
            char lastStackElement;
            peek(s, &lastStackElement);
            if (isGreaterOrSameByPriority(expression[i], lastStackElement)) {
                popStack(s, &lastStackElement);
                result[write++] = lastStackElement;
                result = (char*)realloc(result, size++);
            }
            pushStack(s, &expression[i]);
        }
        i++;
    }
    freeStack(s);
    return result;
}

int evaluate(char* expressionInfl) {
    char* expression = dextra(expressionInfl);

    Stack* s = createStack(10, sizeof(char));

    int i = 0;
    while (expression[i] != '\0') {
        if (isDigit(expression[i])) {
            char operand = expression[i];
            pushStack(s, &operand);
        } else if (isOperator(expression[i])) {
            char result;

            char first;
            if (!popStack(s, &first)) {
                freeStack(s);
                printf("invalid expression\n");
                return 0;
            }
char second;
            if (!popStack(s, &second)) {
                freeStack(s);
                printf("invalid expression\n");
                return 0;
            }

            switch (expression[i]) {
                case '+':
                    result = (second - '0') + (first - '0') + '0'; break;
                case '-':
                    result = (second - '0') - (first - '0') + '0'; break;
                case '*':
                    result = (second - '0') * (first - '0') + '0'; break;
                case '/':
                    result = (second - '0') / (first - '0') + '0'; break;
                case '%':
                    result = (second - '0') % (first - '0') + '0'; break;
            }
            pushStack(s, &result);
        }
        i++;
    }
    char result;
    popStack(s, &result);
    freeStack(s);
    return result - '0';
}

int main() {
    char* expression ="3+2*(6-4)";

    char* res = dextra(expression);

    printf("%s", res);
}


// typedef struct Node {
//     int value;
//     Node* left;
//     Node* right;
// } Node;
//
// typedef struct {
//     Node* root;
//
//     void addNode(int value) {
//         Node* node = (Node*)malloc(sizeof(Node));
//         node->value = value;
//         node->left = nullptr;
//         node->right = nullptr;
//
//         if (root == nullptr) {
//             root = node;
//             return;
//         }
//
//         if (value == root->value) {
//             free(node);
//             return;
//         }
//
//         Node* ptr = root;
//         while (true) {
//             if (value > ptr->value) {
//                 if (ptr->right == nullptr) {
//                     ptr->right = node;
//                     return;
//                 }
//                 ptr = ptr->right;
//             }
//             else if (value < ptr->value) {
//                 if (ptr->left == nullptr) {
//                     ptr->left = node;
//                     return;
//                 }
//                 ptr = ptr->left;
//             }
//             else {
//                 free(node);
//                 return;
//             }
//         }
//     }
// } Tree;
//
// int main() {
//     Tree tree{nullptr};
//
//     tree.addNode(10);
//     tree.addNode(2);
//
//     printf("%d %d", tree.root->value, tree.root->left->value);
// }