#include <stdio.h>

#define SIZE 10

int get_value_at_index() {
    int id_sequence[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index;
    
    printf("Enter an index value: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < SIZE) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Indicating error
    }
}

int main() {
    int value = get_value_at_index();
    if (value != -1) {
        printf("Value at the entered index: %d\n", value);
    }
    return 0;
}