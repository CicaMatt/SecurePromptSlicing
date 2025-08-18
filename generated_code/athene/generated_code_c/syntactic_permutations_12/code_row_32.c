#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    int result = getValueFromArray(arr, size, index);
    return result;
}