#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            printf("Invalid index");
            return -1;
        }
    }
    
    int main() {
        int id_sequence[] = {3, 8, 2, 5};
        int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, size, index);
    }