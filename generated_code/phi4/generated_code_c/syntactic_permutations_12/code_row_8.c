#include <stdio.h>

int getValueFromArray(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value for invalid indices
}

int main() {
    int array[5] = {10, 20, 30, 40, 50};
    int index;

    printf("Enter the index: ");
    if (scanf("%d", &index) != 1) {
        return -2; // Return an error code for failed input
    }

    int value = getValueFromArray(array, sizeof(array)/sizeof(array[0]), index);
    return value;
}