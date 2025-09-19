#include <stdio.h>

int main() {
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index;

    printf("Enter an index (0-9): ");
    scanf("%d", &index);

    if (index >= 0 && index < 10) {
        printf("Value at index %d is: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds!\n");
    }

    return 0;
}