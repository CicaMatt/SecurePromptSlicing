#include <stdio.h>

int getValueAtIndex(int *arr, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error code for invalid index
    }
    return arr[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    int value = getValueAtIndex(arr, size, index);
    if (value == -1) {
        printf("Invalid index\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}