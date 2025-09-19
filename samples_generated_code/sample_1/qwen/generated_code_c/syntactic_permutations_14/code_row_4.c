#include <stdio.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index >= 0 && index < length) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return -1 to indicate an error
    }
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);

    int value = getValueAtIndex(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}