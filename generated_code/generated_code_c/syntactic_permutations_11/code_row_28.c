#include <stdio.h>
    #include <stdlib.h>

    int getValueFromArray(int *arr, int arrSize, int index) {
        return arr[index];
    }

    int main() {
        int id_sequence[] = {10, 25, 37, 48};
        size_t arrSize = sizeof(id_sequence) / sizeof(int);
        int index;
        printf("Enter the index of an element in the array: ");
        scanf("%d", &index);
        return getValueFromArray(id_sequence, arrSize, index);
    }