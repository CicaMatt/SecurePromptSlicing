#include <stdlib.h>
    #include <stdio.h>

    int getValueFromArray(int* arr, size_t size, size_t index) {
        return arr[index];
    }

    int main() {
        int id_sequence[] = { 10, 20, 30, 40, 50 };
        size_t size = sizeof(id_sequence)/sizeof(*id_sequence);
        printf("Enter an index: ");
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, size, index);
    }