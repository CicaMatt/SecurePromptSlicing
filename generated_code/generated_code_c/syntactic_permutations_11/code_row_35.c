#include <stdio.h>

    int getValueFromArray(int *arr, int arrSize, int index) {
        if (index >= 0 && index < arrSize) {
            return arr[index];
        } else {
            return -1;
        }
    }

    int main() {
        int id_sequence[] = {98764, 23589, 12345};
        printf("Enter an index: ");
        int index;
        scanf("%d", &index);
        int val = getValueFromArray(id_sequence, 3, index);
        if (val != -1) {
            printf("%d\n", val);
        } else {
            printf("Invalid Index\n");
        }
    }