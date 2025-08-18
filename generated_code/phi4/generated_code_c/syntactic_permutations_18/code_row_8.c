#include <stdio.h>

int getElementAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error code for out-of-bounds access
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(array) / sizeof(array[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    int result = getElementAtIndex(array, size, index);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}