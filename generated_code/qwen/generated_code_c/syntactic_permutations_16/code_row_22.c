#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(arr) / sizeof(arr[0]);
    int input;

    printf("Enter an index (0-%d): ", size - 1);
    scanf("%d", &input);

    if (input >= 0 && input < size) {
        printf("Value at index %d is %d\n", input, arr[input]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}