#include <stdio.h>

int getValueAtIndex(int *id_sequence, int size) {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return a sentinel value indicating an error
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int result = getValueAtIndex(id_sequence, size);
    if (result != -1) {
        printf("The value at the index is: %d\n", result);
    }
    return 0;
}