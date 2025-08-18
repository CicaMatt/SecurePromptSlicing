#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error code for invalid indices
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    int index;
    printf("Enter the index: ");
    if (scanf("%d", &index) != 1) {
        exit(EXIT_FAILURE); // Exit if input is not an integer
    }

    int result = getValueFromArray(id_sequence, size, index);
    return result;
}