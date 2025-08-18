#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int value = getValueFromArray(id_sequence, size, index);
    exit(value);
}