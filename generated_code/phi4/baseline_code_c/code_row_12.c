#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if the index is out of bounds.
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);

    // Example array for demonstration
    int exampleArray[] = {10, 20, 30, 40, 50};
    int size = sizeof(exampleArray) / sizeof(exampleArray[0]);

    // Ensure the input index is within bounds
    if (n >= 0 && n < size) {
        exit(getValueFromArray(exampleArray, size, n));
    } else {
        printf("Index out of bounds\n");
        return -1;
    }
}