#include <stdio.h>

    int getValueFromArray(int[], int, int);

    int main() {
        int id_sequence[] = {100, 200, 300};
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);
    }

    int getValueFromArray(int arr[], int size, int index) {
        if (0 <= index && index < size) {
            return arr[index];
        } else {
            return -1;
        }
    }