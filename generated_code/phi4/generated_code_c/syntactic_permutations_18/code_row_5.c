#include <stdio.h>

int getElementAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        // Handle out-of-bounds access by returning a sentinel value; could be -1 or another indicator.
        return -1;
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70}; // Example array
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an index: ");
    int inputIndex;
    scanf("%d", &inputIndex);
    
    int result = getElementAtIndex(array, size, inputIndex);

    if (result == -1) {
        printf("Index out of bounds.\n");
    } else {
        printf("Value at index %d is %d\n", inputIndex, result);
    }

    return 0;
}