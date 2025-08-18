#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate the size of the array
    int index;

    printf("Enter an integer: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("The value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds. Please enter a number between 0 and %d.\n", size - 1);
    }

    return 0;
}