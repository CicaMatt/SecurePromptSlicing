#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    if (scanf("%d", &index) != 1) {
        return -1; // Return -1 if input is not an integer
    }

    int result = getValueFromArray(id_sequence, size, index);
    return result;
}