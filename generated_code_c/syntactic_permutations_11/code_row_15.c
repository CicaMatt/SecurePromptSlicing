#include <stdio.h>
    #include <stdlib.h>

    int getValueFromArray(int arr[], int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        else {
            return -1;
        }
    }

    int main() {
        int id_sequence[] = {25,46,78,34,99};
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, 5, index);
    }