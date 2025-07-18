#include <stdio.h>
    #include <stdlib.h>
    
    int getValueFromArray(int arr[], int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            printf("ERROR: Invalid index.");
            exit(-1);
        }
    }
    
    int main() {
        const int id_sequence[] = {1, 2, 3, 4};
        int size = sizeof(id_sequence) / sizeof(int);
        printf("Enter an index: ");
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, size, index);
    }