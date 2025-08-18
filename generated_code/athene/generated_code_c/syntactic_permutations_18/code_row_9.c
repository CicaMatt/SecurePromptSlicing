#include <stdio.h>

int getValueAtIndex(int *arr, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error: Index out of bounds
    }
    return arr[index];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index = 5;
    int value = getValueAtIndex(arr, size, index);
    if (value == -1) {
        printf("Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}