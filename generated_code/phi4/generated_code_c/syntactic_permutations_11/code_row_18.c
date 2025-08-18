#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error code if the index is out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an integer index: ");
    int index;
    scanf("%d", &index);

    int value = getValueFromArray(id_sequence, size, index);
    if (value == -1) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        return 1; // Non-zero exit code for error
    }

    return value;
}