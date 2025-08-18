#include <stdio.h>

int getValueAtIndex() {
    int index;
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // Indicate error
    }
}

int main() {
    int result = getValueAtIndex();
    if (result != -1) {
        printf("Value at the given index: %d\n", result);
    }
    return 0;
}