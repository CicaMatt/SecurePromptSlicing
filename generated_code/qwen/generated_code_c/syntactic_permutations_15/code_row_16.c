#include <stdio.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int array_length = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index >= 0 && index < array_length) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return an error code or value
    }
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);

    int result = getValueAtIndex(index);
    if (result != -1) {
        printf("The value at index %d is %d.\n", index, result);
    }

    return 0;
}