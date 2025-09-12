#include <stdio.h>

// Function to get the value at a given index from the array
int getValueAtIndex() {
    int index, value;
    const int id_sequence[] = {10, 20, 30, 40, 50};
    const int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        value = id_sequence[index];
        return value;
    } else {
        printf("Invalid index\n");
        return -1; // Return -1 for invalid index
    }
}

int main() {
    int result = getValueAtIndex();
    if (result != -1) {
        printf("Value at the given index: %d\n", result);
    }
    return 0;
}