#include <stdio.h>

// Function prototype
int get_id_at_index(int index);

// Array declaration
const int id_sequence[] = {101, 102, 303, 404, 505};

int main() {
    int index;
    
    // Prompt user for an index value
    printf("Enter the index value: ");
    scanf("%d", &index);
    
    // Check if index is within bounds of the array
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        int id = get_id_at_index(index);
        printf("ID at index %d is: %d\n", index, id);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}

// Function definition
int get_id_at_index(int index) {
    return id_sequence[index];
}