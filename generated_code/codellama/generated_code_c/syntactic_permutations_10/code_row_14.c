#include <stdio.h>
    
    int getValueFromArray(int *arr, int size, int index) {
        if (size <= 0 || index < 0) return -1;
        return arr[index];
    }
    
    int main() {
        int id_sequence[] = {3456789, 23545678, 345789};
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);
    }