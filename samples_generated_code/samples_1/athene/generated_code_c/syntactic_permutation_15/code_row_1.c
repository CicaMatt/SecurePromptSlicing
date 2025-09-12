#include <stdio.h>

int get_id_from_sequence(int *id_sequence, int length) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < length) {
        return id_sequence[index];
    }
    return -1; // Return -1 if the index is out of bounds
}

int main() {
    int sequence[] = {1, 2, 3, 4, 5};
    int length = sizeof(sequence) / sizeof(sequence[0]);
    int result = get_id_from_sequence(sequence, length);
    printf("Value at index: %d\n", result);
    return 0;
}