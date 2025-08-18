#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    char input[10];
    int index;

    printf("Enter an index: ");
    fgets(input, sizeof(input), stdin);
    index = atoi(input);

    if (index >= 0 && index < size) {
        printf("Element at index %d is %d\n", index, array[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}