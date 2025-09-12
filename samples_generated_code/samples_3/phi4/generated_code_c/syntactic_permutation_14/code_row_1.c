#include <stdio.h>

#define SIZE 10

int get_value_at_index(int* id_sequence, int size) {
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Return a sentinel value indicating error
    }
}

int main() {
    int id_sequence[SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    int result = get_value_at_index(id_sequence, SIZE);
    if (result != -1) {
        printf("Value at index: %d\n", result);
    }
    
    return 0;
}