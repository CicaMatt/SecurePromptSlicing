#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Error value for out-of-bounds access
}

int main() {
    int id_sequence[] = {1, 2, 3, 4, 5};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;
    
    if (scanf("%d", &index) != 1) {
        return -1; // Error value for invalid input
    }
    
    int value = getValueFromArray(id_sequence, size, index);
    return value;
}