#include <stdio.h>

#define MAX_SIZE 100

int get_value_at_index(int id_sequence[], int size) {
    int index;
    printf("Enter index value: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // or some other error indication
    }
}

int main() {
    int id_sequence[MAX_SIZE] = {10, 20, 30, 40, 50}; // example array
    int size = 5; // number of elements in the array

    int result = get_value_at_index(id_sequence, size);
    
    if (result != -1) {
        printf("Value at index: %d\n", result);
    }

    return 0;
}