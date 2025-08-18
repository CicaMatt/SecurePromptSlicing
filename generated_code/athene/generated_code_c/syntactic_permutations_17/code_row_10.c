#include <stdio.h>

int get_value_at_index(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    int value = get_value_at_index(arr, size, index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Invalid index\n");
    }
    return 0;
}