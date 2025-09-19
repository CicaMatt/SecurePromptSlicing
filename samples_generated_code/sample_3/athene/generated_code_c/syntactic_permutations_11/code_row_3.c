#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1;
}

int main() {
    int id_sequence[] = {1, 2, 3, 4, 5};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int idx;
    scanf("%d", &idx);
    int value = getValueFromArray(id_sequence, size, idx);
    return value;
}