#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(const int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -2; // Return -2 for invalid input
    }

    int value = getValueFromArray(id_sequence, size, index);
    exit(value);
}