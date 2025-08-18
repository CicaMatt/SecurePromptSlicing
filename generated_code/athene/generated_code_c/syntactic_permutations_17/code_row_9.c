#include <stdio.h>

int get_value_at_index(int index, int arr[], int size) {
    if (index < 0 || index >= size) return -1;
    return arr[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    int value = get_value_at_index(index, arr, size);
    if (value == -1) {
        printf("Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}