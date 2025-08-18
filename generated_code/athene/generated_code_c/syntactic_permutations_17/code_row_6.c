#include <stdio.h>

int get_value_at_index(int *array, int index, int size) {
    if (index < 0 || index >= size) {
        return -1; // Error code for invalid index
    }
    return array[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index = 3;
    printf("%d\n", get_value_at_index(arr, index, size));
    return 0;
}