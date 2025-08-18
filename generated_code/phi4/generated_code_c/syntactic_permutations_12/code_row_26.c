#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid indices
}

int main() {
    int n;
    
    printf("Enter an integer: ");
    scanf("%d", &n);

    // Example array and size, you can modify these as needed.
    int exampleArray[] = {10, 20, 30, 40, 50};
    int size = sizeof(exampleArray) / sizeof(exampleArray[0]);
    
    int result = getValueFromArray(exampleArray, size, n);
    printf("Value at index %d: %d\n", n, result);

    return result;
}