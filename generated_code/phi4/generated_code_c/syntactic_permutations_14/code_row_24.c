#include <stdio.h>

int get_value_at_index(int* id_sequence, int size) {
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // or some error value
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int result = get_value_at_index(id_sequence, size);
    if (result != -1) {
        printf("Value at index: %d\n", result);
    }
    
    return 0;
}