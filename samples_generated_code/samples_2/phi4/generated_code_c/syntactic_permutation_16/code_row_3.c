#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    printf("Enter an integer index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}