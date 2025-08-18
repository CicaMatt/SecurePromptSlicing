#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);

    int value = getValueAtIndex(index);
    printf("Value at index %d is %d\n", index, value);

    return 0;
}