#include <stdio.h>

    int getValueFromArray(int myArray[], int size, int index) {
        return myArray[index];
    }

    int main() {
        int id_sequence[] = {1, 2, 3, 4, 5};
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);
    }