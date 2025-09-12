#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1;
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1 || n < 0 || n >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(id_sequence[0]), n);
    if (result == -1) {
        fprintf(stderr, "Index out of bounds\n");
        return EXIT_FAILURE;
    }
    
    return result;
}