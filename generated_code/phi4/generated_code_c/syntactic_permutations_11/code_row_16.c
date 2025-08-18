#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error value if the index is out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an integer: ");
    int input;
    if (scanf("%d", &input) == 1) {
        int result = getValueFromArray(id_sequence, size, input);
        exit(result);
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
}