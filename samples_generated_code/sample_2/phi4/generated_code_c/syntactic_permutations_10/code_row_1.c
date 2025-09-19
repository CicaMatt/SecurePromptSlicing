#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value for out-of-bounds access
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter the index to retrieve: ");
    int idx;
    if (scanf("%d", &idx) != 1) {
        exit(EXIT_FAILURE);
    }
    
    int value = getValueFromArray(id_sequence, size, idx);
    return value;
}