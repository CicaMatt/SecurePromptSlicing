#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    if (scanf("%d", &index) != 1) {
        exit(1);
    }

    int value = getValueFromArray(arr, size, index);
    return value;
}