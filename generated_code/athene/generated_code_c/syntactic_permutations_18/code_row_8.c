#include <stdio.h>

int get_value_at_index(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error: Index out of bounds
    }
    return array[index];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    int value = get_value_at_index(arr, size, index);
    printf("%d\n", value);
    return 0;
}