#pragma once
#include <climits>
#include <cstdlib>

#include "stack.h"

// таска

// бинарное дерево
// обходы: прямой обход, обратный, симметричный

namespace MyBinaryTree {
    typedef struct Node {
        int value;
        Node *left;
        Node *right;
        Node *parent;
    } Node;

    typedef struct {
        Node *root;
    } Tree;

    Tree *initTree(int rootValue) {
        Tree *tree = (Tree*)malloc(sizeof(Tree));

        Node *root = (Node*)malloc(sizeof(Node));
        root->value = rootValue;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;

        tree->root = root;

        return tree;
    }

    Node *addLeftChild(Node *parent, int value) {
        Node *child = (Node*)malloc(sizeof(Node));
        child->value = value;
        child->left = nullptr;
        child->right = nullptr;
        child->parent = parent;

        parent->left = child;

        return child;
    }

    Node *addRightChild(Node *parent, int value) {
        Node *child = (Node*)malloc(sizeof(Node));
        child->value = value;
        child->left = nullptr;
        child->right = nullptr;
        child->parent = parent;

        parent->right = child;

        return child;
    }

    void preorderSearch(Node *cur) {
        if (cur == nullptr) return;

        printf("%d\n", cur->value);
        preorderSearch(cur->left);
        preorderSearch(cur->right);
    }

    // 894526731
    void postorderSearch(Node *cur) {
        if (cur == nullptr) return;

        postorderSearch(cur->left);
        postorderSearch(cur->right);
        printf("%d\n", cur->value);
    }

    void inorderSearch(Node *cur) {
        if (cur == nullptr) return;

        inorderSearch(cur->left);
        printf("%d\n", cur->value);
        inorderSearch(cur->right);
    }


    // 1. прямой обратный симетричный обходы бинарного
    // 2. найти высоту бинарного
    // 3. проверить является ли деревом поиска
    // 4. проверить сбалансировано ли (разница высот между ветками не больше одного)

    int findHeight(Node *cur) {
        if (cur == nullptr) return -1;

        int h1 = findHeight(cur->left);
        int h2 = findHeight(cur->right);

        int h = h1;
        if (h1 < h2) h = h2;

        // printf("%d >> %d\n", cur->value, h + 1);

        return h + 1;
    }

    int isBalanced(Node *cur) {
        if (cur == nullptr) return 1;

        int h1 = findHeight(cur->left);
        int h2 = findHeight(cur->right);

        int dif = h1 - h2;
        dif = dif < 0 ? -dif : dif;
        if (dif > 1) return 0;

        return isBalanced(cur->left) && isBalanced(cur->right);
    }

    int isSearchTree(Node *cur, int minValue, int maxValue) {
        if (cur == nullptr) return 1;

        printf("%d (%d) %d\n", minValue, cur->value, maxValue);

        if (cur->value <= minValue || cur->value >= maxValue) {
            return 0;
        }

        return isSearchTree(cur->left, minValue, cur->value) && isSearchTree(cur->right, cur->value, maxValue);
    }

    void run() {
        Tree *tree = initTree(6);

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
        //
        // Node *rightChild3 = addRightChild(rightChild2, 10);
        //
        // addRightChild(rightChild3, 11);

        Node *node3 = addLeftChild(tree->root, 3);
        Node *node9 = addRightChild(tree->root, 9);

        Node *node1 = addLeftChild(node3, 1);
        Node *node5 = addRightChild(node3, 5);

        Node *node10 = addRightChild(node9, 10);


        printf("%d", isSearchTree(tree->root, -INT_MAX, INT_MAX));
    }
}