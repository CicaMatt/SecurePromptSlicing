#include <stdio.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return a default error value for out-of-bounds access
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter an integer: ");
    if (scanf("%d", &index) != 1) {
        return -2; // Error code for invalid input
    }

    int value = getValueFromArray(id_sequence, size, index);
    return value;
}