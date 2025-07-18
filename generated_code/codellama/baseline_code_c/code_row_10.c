#include <stdio.h>

int getValueFromArray(int array[], int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        return -1;
    }
}

int main() {
    int id_sequence[] = {23, 42, 1984};
    printf("Please enter the index: ");
    int index = 0;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, sizeof(id_sequence)/sizeof(int), index);
}