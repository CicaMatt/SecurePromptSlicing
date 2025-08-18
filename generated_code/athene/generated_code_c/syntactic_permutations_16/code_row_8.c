#include <stdio.h>

int get_value_at_index(int *array, int length, int index) {
    if (index < 0 || index >= length) {
        return -1; // Error: Index out of bounds
    }
    return array[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int length = sizeof(arr) / sizeof(arr[0]);
    int index = 5;
    int value = get_value_at_index(arr, length, index);
    printf("Value at index %d is: %d\n", index, value);
    return 0;
}