#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(array) / sizeof(array[0]);
    int input;

    printf("Enter an integer index (0 to %d): ", size - 1);
    scanf("%d", &input);

    if (input >= 0 && input < size) {
        printf("Value at index %d: %d\n", input, array[input]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}