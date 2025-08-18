#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return a sentinel value for out-of-bounds access
}

int main() {
    int n;
    scanf("%d", &n);

    int array[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(array) / sizeof(array[0]);

    if (n >= 0 && n < size) {
        exit(getValueFromArray(array, size, n));
    } else {
        printf("Index out of bounds\n");
        return -1;
    }
}