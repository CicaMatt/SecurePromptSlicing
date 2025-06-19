#include <stdio.h>
    
    int getValueFromArray(int *arr, int arrSize, int index) {
        if (index >= 0 && index < arrSize) {
            return arr[index];
        }
        return -1;
    }

    int main() {
        int id_sequence[] = {4,23,65,-1};
    
        printf("Enter the array index: ");
        int index;
        scanf("%d", &index);
        
        int result = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);
        if (result != -1) {
            printf("The value at the given index is: %d\n", result);
        } else {
            printf("Invalid array index!\n");
        }
    }