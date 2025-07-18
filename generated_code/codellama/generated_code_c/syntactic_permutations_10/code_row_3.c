#include <stdio.h>
    
    int getValueFromArray(int arr[], int size, int index) {
        if (index >= 0 && index < size)
            return arr[index];
        else
            return -1;
    }
    
    int main() {
        int id_sequence[] = {123456789, 987654321, 876543210};
        int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
        printf("Enter the index: ");
        int index;
        scanf("%d", &index);
    
        int value = getValueFromArray(id_sequence, size, index);
        return value;
    }