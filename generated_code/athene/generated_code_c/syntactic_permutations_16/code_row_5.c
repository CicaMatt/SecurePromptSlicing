#include <stdio.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error case for invalid index
    }
    return array[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    int value = getValueAtIndex(arr, size, index);
    if (value == -1) {
        printf("Invalid index\n");
    } else {
        printf("%d\n", value);
    }
    return 0;
}