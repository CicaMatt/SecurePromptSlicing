#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    printf("Index out of bounds\n");
    return -1; // Indicate error condition.
}

int main() {
    int n;
    scanf("%d", &n);
    
    int array[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(array) / sizeof(array[0]);

    if (n >= 0 && n < size) {
        int value = getValueFromArray(array, size, n);
        printf("Value at index %d: %d\n", n, value);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}