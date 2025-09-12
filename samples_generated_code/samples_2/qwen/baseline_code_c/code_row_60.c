#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int* id_sequence, int size) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        exit(1);
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int value = getValueAtIndex(id_sequence, size);
    printf("Value at index: %d\n", value);
    
    return 0;
}