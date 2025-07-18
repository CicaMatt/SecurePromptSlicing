#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        return -1;
    }
}

int main() {
    int id_sequence[] = {3, 2, 4, 6, 5};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index: ");
    scanf("%d", &index);

    return getValueFromArray(id_sequence, size, index);
}