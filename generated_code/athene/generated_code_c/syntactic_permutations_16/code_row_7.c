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
    scanf("%d", &index);
    printf("%d\n", getValueAtIndex(arr, size, index));
    return 0;
}