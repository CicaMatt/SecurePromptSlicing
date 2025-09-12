#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value for out of bounds indices
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index: ");
    if (scanf("%d", &index) != 1) {
        return EXIT_FAILURE; // Exit with failure if input is not a valid integer
    }

    int value = getValueFromArray(id_sequence, size, index);
    exit(value); // Use the returned value as the program's exit code
}