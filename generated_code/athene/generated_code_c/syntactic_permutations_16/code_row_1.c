#include <stdio.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error code for invalid index
    }
    return array[index];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    printf("%d\n", getValueAtIndex(arr, size, index));
    return 0;
}