#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 if index is out of bounds
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    scanf("%d", &index);

    int result = getValueAtIndex(arr, size, index);
    return result;
}