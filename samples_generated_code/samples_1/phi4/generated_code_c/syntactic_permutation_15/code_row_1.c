#include <stdio.h>

int get_value_at_index() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicating an error with a sentinel value
    }
}

int main() {
    int result = get_value_at_index();
    if (result != -1) {  // Check for error condition
        printf("Value at the given index: %d\n", result);
    }
    return 0;
}