#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value for out-of-bounds access
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index: ");
    if (scanf("%d", &size) != 1 || size < 0) {
        return -2; // Return an invalid exit code for input error
    }

    int value = getValueFromArray(id_sequence, size, size);
    
    return value;
}