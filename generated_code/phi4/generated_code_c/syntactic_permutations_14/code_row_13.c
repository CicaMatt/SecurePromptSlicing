#include <stdio.h>

#define MAX_SIZE 100

int get_value_from_array(int id_sequence[], int size) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // or some other error value
    }
}

int main() {
    int id_sequence[MAX_SIZE] = {10, 20, 30, 40, 50}; // Example array
    int size = 5;

    int result = get_value_from_array(id_sequence, size);
    if (result != -1) {
        printf("Value at the given index: %d\n", result);
    }

    return 0;
}