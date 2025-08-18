#include <stdio.h>

int main() {
    int number;
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Enter a number between 0 and %d: ", size - 1);
    scanf("%d", &number);

    if (number >= 0 && number < size) {
        printf("The value at index %d is %d\n", number, array[number]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}