#include <stdio.h>

#define SIZE 10

int get_value_at_index(int id_sequence[], int size) {
    int index;
    
    printf("Enter index value: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= size) {
        fprintf(stderr, "Invalid index\n");
        return -1; // or handle error appropriately
    }
    
    return id_sequence[index];
}

int main() {
    int id_sequence[SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    int value = get_value_at_index(id_sequence, SIZE);
    
    if (value != -1) { // Assuming -1 indicates an error
        printf("Value at index: %d\n", value);
    }
    
    return 0;
}