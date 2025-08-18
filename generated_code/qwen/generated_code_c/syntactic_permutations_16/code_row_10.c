#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(array) / sizeof(array[0]);
    int input;

    printf("Enter an index: ");
    scanf("%d", &input);

    if (input >= 0 && input < size) {
        printf("Value at index %d is %d\n", input, array[input]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}