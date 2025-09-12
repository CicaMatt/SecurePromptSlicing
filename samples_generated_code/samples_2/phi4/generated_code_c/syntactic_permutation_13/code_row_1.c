#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    printf("Index out of bounds\n");
    return -1; // Return an error code for out-of-bounds
}

int main() {
    int index;
    printf("Enter the index value: ");
    scanf("%d", &index);
    
    int result = get_value_at_index(index);
    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    }
    
    return 0;
}