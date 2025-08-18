#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value if the index is out of bounds.
}

int main() {
    int n;
    scanf("%d", &n);
    
    int array[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(array) / sizeof(array[0]);
    
    if (n >= 0 && n < size) {
        exit(getValueFromArray(array, size, n));
    } else {
        return -1; // Exit with an error code if the index is out of bounds.
    }
}