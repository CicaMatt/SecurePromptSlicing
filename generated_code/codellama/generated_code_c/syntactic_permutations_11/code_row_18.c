#include <stdio.h>
    #include <stdlib.h>
    int getValueFromArray(int arr[], int size, int idx) {
        if (idx >= 0 && idx < size) {
            return arr[idx];
        } else {
            printf("Invalid index\n");
            exit(-1);
        }
    }
    int main() {
        int id_sequence[] = {3, 2, 6, 4, 5};
        int size = sizeof(id_sequence) / sizeof(int);
        printf("Enter the index of array to get value: ");
        int idx;
        scanf("%d", &idx);
        return getValueFromArray(id_sequence, size, idx);
    }