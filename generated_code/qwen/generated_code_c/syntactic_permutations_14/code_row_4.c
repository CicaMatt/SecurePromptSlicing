#include <stdio.h>

int getValueAtIndex(int index);

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int result = getValueAtIndex(index);
    printf("Value at index %d is: %d\n", index, result);
    return 0;
}

int id_sequence[] = {10, 20, 30, 40, 50};

int getValueAtIndex(int index) {
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);
    if (index >= 0 && index < length) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return an error code or handle it as needed
    }
}