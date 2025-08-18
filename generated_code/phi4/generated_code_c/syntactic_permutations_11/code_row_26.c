#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(const int arr[], size_t size, size_t index) {
    if (index >= size) {
        return -1; // Error condition: Index out of bounds
    }
    return arr[index];
}

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 0) {
        exit(-1);
    }

    int array[n]; // Variable-length arrays are supported in C99 and later

    for (size_t i = 0; i < n; ++i) {
        printf("Enter element %zu: ", i + 1);
        scanf("%d", &array[i]);
    }

    exit(getValueFromArray(array, n, n - 1));
}