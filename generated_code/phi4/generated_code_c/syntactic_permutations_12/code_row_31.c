#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error code if the index is out of bounds
}

int main() {
    int n;
    printf("Enter the value at which you want to get: ");
    scanf("%d", &n);

    int array[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(array) / sizeof(array[0]);

    int result = getValueFromArray(array, size, n);
    
    if (result != -1) {
        printf("Value at index %d is: %d\n", n, result);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}