#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if the index is out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an integer: ");
    int index;
    scanf("%d", &index);
    
    int value = getValueAtIndex(id_sequence, size, index);
    return value;
}