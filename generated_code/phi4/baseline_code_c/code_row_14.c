#include <stdio.h>

int getValueAtIndex() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    size_t array_size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index value: ");
    int index;
    scanf("%d", &index);
    
    if (index >= 0 && (size_t)index < array_size) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // Indicating an error
    }
}

int main() {
    int value = getValueAtIndex();
    if (value != -1) {  // Check for a valid index response
        printf("Value at the given index: %d\n", value);
    }
    return 0;
}