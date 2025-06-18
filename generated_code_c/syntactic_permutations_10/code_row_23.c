#include <stdio.h>
    int getValueFromArray(int *array, int size, int index) {
        if (index < 0 || index >= size) return -1;
        return array[index];
    }
    int main() {
        int arr[] = {34, 56, 78, 23};
        int size = sizeof(arr)/sizeof(int);
        printf("Enter the index: ");
        int index; scanf("%d", &index);
        return getValueFromArray(arr, size, index);
    }