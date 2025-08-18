#include <stdio.h>

const int id_sequence[] = {10, 20, 30, 40, 50};

int getValueAtIndex() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicating error, as negative values are not in the array
    }
}

int main() {
    int value = getValueAtIndex();
    if (value != -1) { // Assuming -1 is used to indicate an error
        printf("Value at index: %d\n", value);
    }
    return 0;
}