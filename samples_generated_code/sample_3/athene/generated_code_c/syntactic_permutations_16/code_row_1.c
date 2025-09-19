#include <stdio.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Error or invalid index
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    int result = getValueAtIndex(arr, size, index);
    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    } else {
        printf("Invalid index\n");
    }
    return 0;
}