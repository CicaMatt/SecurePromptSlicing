#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // or some error value indicating out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -2; // Error code for invalid input
    }

    int result = getValueFromArray(id_sequence, size, index);
    exit(result);
}