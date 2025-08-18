#include <stdio.h>

#define SIZE 10

int id_sequence[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int get_value_at_index(int index) {
    if (index >= 0 && index < SIZE) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Return an invalid value or handle as needed
    }
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);

    int result = get_value_at_index(index);
    if (result != -1) { // Check for valid result before printing
        printf("Value at index %d is: %d\n", index, result);
    }

    return 0;
}