#include <stdio.h>

int get_value_at_index(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error code for invalid index
    }
    return array[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    int value = get_value_at_index(arr, size, index);
    if (value == -1) {
        printf("Invalid index\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}