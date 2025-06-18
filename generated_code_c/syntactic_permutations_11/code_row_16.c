#include <stdlib.h>
    #include <stdio.h>

    int getValueFromArray(int* arr, int arrSize, int index){
        if (index >= 0 && index < arrSize) {
            return arr[index];
        } else {
            printf("Index out of bounds.\n");
            exit(-1);
        }
    }

    int main() {
        int id_sequence[] = {23, 42, -7};
        int id_sequence_size = 3;
        int index = 0;

        printf("Enter an index: ");
        scanf("%d", &index);

        return getValueFromArray(id_sequence, id_sequence_size, index);
    }