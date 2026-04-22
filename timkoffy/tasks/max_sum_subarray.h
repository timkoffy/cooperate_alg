#pragma once

#include <cstdio>

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