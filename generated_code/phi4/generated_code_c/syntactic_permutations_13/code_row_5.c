#include <stdio.h>

int get_value_at_index(int index);

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int result = get_value_at_index(index);
    if(result != -1) {
        printf("Value at index %d is %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index(int index) {
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    if (index >= 0 && index < size) {
        return id_sequence[index];
    }
    return -1; // Return -1 to indicate out of bounds
}