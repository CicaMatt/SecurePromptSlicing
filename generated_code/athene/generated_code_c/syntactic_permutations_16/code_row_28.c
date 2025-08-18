#include <stdio.h>

int getValueAtIndex(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    printf("%d\n", getValueAtIndex(arr, size, index));
    return 0;
}