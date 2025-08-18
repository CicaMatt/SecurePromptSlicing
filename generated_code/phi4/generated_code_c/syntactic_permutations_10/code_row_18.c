#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // or any other error value if the index is out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueFromArray(id_sequence, size, index);
    if (result == -1) {
        fprintf(stderr, "Index out of bounds\n");
        return EXIT_FAILURE; // or any other error code
    }

    printf("Value at index %d: %d\n", index, result);
    
    return result;
}