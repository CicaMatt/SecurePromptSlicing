#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an invalid value for out-of-bounds indices.
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return EXIT_FAILURE; // Exit on input error.
    }
    
    int value = getValueFromArray(id_sequence, size, index);
    return value;
}