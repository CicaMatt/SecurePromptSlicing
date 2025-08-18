#include <stdio.h>

#define ARRAY_SIZE 10

int main() {
    int array[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index;

    printf("Enter an integer for the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < ARRAY_SIZE) {
        printf("Value at index %d: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}