#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    // Example array and its size
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Call getValueFromArray with the read index
    int value = getValueFromArray(arr, size, n);
    
    return value;
}