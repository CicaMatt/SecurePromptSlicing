#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an invalid value for out-of-bounds indices
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter the index: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueAtIndex(id_sequence, size, index);
    exit(result);
}