#include "solutions.h"
#include <stdlib.h>

int running_total(int value) {
    static int total = 0;
    total += value;
    return total;
}

int* reverse(const int* arr, int length) {
    int* reversed = (int*)calloc(length, sizeof(int));
    for (int i = 0; i < length; i++) {
        reversed[i] = arr[length - 1 - i];
    }
    return reversed;
}

void reverse_in_place(int* arr, int length) {
    for (int i = 0; i < length / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[length - 1 - i];
        arr[length - 1 - i] = temp;
    }
}

int num_occurences(const int* arr, int length, int value) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    return count;
}