#include <csignal>
#include <unistd.h>

#include "timkoffy/data_structures/binary_tree.h"
#include "timkoffy/data_structures/bloom_filter.h"
#include "timkoffy/data_structures/graph_adjmatrix.h"
#include "timkoffy/tasks/A-star_field_visualization.h"
#include "timkoffy/tasks/render_graph.h"

void clearFlags(char *exists, char *str, int i, int j) {
    for (int k = i; k <= j; k++) {
        char ch = str[k];
        exists[(int)ch] = 0;
    }
}

void printSubstr(char *str, int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

void printExists(char *exists) {
    for (int i = 'a'; i < 'z'; i++) {
        printf("%c ", i);
    }
    printf("\n");
    for (int i = 'a'; i < 'z'; i++) {
        printf("%i ", exists[i]);
    }
    printf("\n");
}

int getUniquePattern(char *str) {
    char *exists = (char*)calloc(256, sizeof(char));

    int maxLen = 0;
    int left = 0;
    for (int right = 0; str[right] != '\0'; right++) {
        char rightChar = str[right];
        while (exists[rightChar] == 1 && left < right) {
            char leftChar = str[left];
            exists[leftChar] = 0;
            left++;
        }

        exists[(int)rightChar] = 1;

        int subLen = right - left + 1;
        maxLen = maxLen < subLen ? subLen : maxLen;
        printSubstr(str, left, right);
    }

    free(exists);
    return maxLen;
}






int calculateSum(int *arr, int start, int end) {
    int res = 0;
    for (int i = start; i <= end; i++) {
        res += arr[i];
    }
    return res;
}

void printSubArray(int *arr, int start, int end) {
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int maxSum(int *arr, int size) {
    int left = 0;

    int maxSum = 0;
    for (int i = 0; i < size; i++) {
        if (maxSum > arr[i]) maxSum = arr[i];
    }

    for (int right = 0; right < size; right++) {
        int curSum = calculateSum(arr, left, right);
        printSubArray(arr, left, right + 1);

        while (curSum < maxSum && left < right) {
            curSum -= arr[left];
            left++;
        }

        maxSum = maxSum < curSum ? curSum : maxSum;
    }
    return maxSum;
}

int maxSu(int *arr, int size) {
    int res = arr[0];
    int maxSum = arr[0];

    int left = 0;
    int right = 1;
    int tmpLeft = 0;
    for (int i = 1; i < size; i++) {
        res += arr[i];

        if (res < arr[i]) {
            tmpLeft = i;
            res = arr[i];
        }

        if (res > maxSum) {
            left = tmpLeft;
            right = i + 1;
            maxSum = res;
        }
    }

    printSubArray(arr, left, right);
    return maxSum;
}

// таска на дз

// вход: массив строк
// выход: массив групп строк анаграмм

// 1. для каждого слова мапа (символ: колво встреч)
// 2. для каждого слова проверяем мапы с каждой мапой последующих слов
// 3. если длина различна смысла сравнивать нет



// таска

// бинарное дерево
// обходы: прямой обход, обратный, симметричный

int main() {
    runAStar();

    // using namespace MyBinaryTree;
    // Tree *tree = initTree();
    //
    // Node *leftChild0 = addLeftChild(tree->root, 2);
    // Node *rightChild0 = addRightChild(tree->root, 3);
    //
    // Node *leftChild1 = addLeftChild(leftChild0, 4);
    // Node *rightChild1  = addRightChild(leftChild0, 5);
    //
    // Node *leftChild2 = addLeftChild(leftChild1, 8);
    // Node *rightChild2  = addRightChild(leftChild1, 9);
    //
    // Node *leftChild01 = addLeftChild(rightChild0, 6);
    // Node *rightChild01  = addRightChild(rightChild0, 7);
    // //
    // Node *rightChild3 = addRightChild(rightChild2, 10);
    //
    // addRightChild(rightChild3, 11);
    //
    //
    // printf("%d", findHeightUnwrapped(tree->root));

    // straightSearch(tree, tree->root);

    //
    // reversedSearch(tree->root);





    // int arr[] = {-100, 99, 199, -10000, 200};
    // int size = sizeof(arr) / sizeof(int);
    // printf("%d", maxSu(arr, size));

    // char *str = "aaaaa";
    //
    // printf("%s\n", str);
    //
    // int res = getUniquePattern(str);
    // printf("%d", res);
}