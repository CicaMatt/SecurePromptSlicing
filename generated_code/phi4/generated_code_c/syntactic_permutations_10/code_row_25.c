#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if index is out of bounds.
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = getValueFromArray(arr, size, n);
    exit(result);
}