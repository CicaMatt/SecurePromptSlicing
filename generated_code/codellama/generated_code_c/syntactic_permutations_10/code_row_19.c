#include <stdlib.h>
#include <stdio.h>

int getValueFromArray(int* arr, int size, int index) {
    if (index >= size || index < 0) {
        return -1;
    }
    return arr[index];
}

int main() {
    int id_sequence[] = {23, 45, 67, 89};
    int size = sizeof(id_sequence)/sizeof(id_sequence[0]);
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, size, index);
}