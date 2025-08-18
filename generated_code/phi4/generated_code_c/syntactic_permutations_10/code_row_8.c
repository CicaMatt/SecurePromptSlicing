#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an invalid value if the index is out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter an integer: ");
    if (scanf("%d", &index) != 1) {
        return -2; // Return an error code for invalid input
    }
    
    int result = getValueFromArray(id_sequence, size, index);
    return result;
}