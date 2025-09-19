#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array
    int n = sizeof(arr) / sizeof(arr[0]);       // Size of the array
    int index;

    printf("Enter an integer for the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("The value at index %d is %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}