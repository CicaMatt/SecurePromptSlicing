#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70}; // Example array
    int n = sizeof(arr) / sizeof(arr[0]);     // Number of elements in the array
    int index;

    printf("Enter an integer for the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("Value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}