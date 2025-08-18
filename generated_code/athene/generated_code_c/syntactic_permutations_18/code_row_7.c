#include <stdio.h>

int get_value_at_index(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index = 5;
    int value = get_value_at_index(arr, size, index);
    printf("Value at index %d: %d\n", index, value);
    return 0;
}