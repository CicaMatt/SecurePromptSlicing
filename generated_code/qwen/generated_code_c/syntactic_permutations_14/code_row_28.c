#include <stdio.h>

int getValueAtIndex(int *array, int size) {
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Returning -1 to indicate an error
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int value = getValueAtIndex(arr, size);
    if (value != -1) {
        printf("Value at index: %d\n", value);
    }
    return 0;
}