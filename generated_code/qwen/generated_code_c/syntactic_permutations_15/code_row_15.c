#include <stdio.h>

int getValueAtIndex(int index, const int* sequence, int length) {
    if (index >= 0 && index < length) {
        return sequence[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index value: ");
    scanf("%d", &index);

    int value = getValueAtIndex(index, id_sequence, length);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Invalid index\n");
    }

    return 0;
}