#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5}; // Example array, can be modified as needed
    int index, size = sizeof(arr) / sizeof(arr[0]);

    printf("Enter the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Value at index %d is %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds!\n");
    }

    return 0;
}