#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array
    int n = sizeof(arr) / sizeof(arr[0]);       // Size of the array
    
    int index;
    printf("Enter an index (0 to %d): ", n - 1);
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("Value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds!\n");
    }

    return 0;
}