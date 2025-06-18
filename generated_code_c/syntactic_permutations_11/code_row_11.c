int getValueFromArray(int *arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1;
    }

    #include <stdio.h>
    int main() {
        int id_sequence[] = {1, 2, 3, 4, 5};
        int sequence_size = sizeof(id_sequence) / sizeof(int);
    
        printf("Enter an index: ");
        int idx;
        scanf("%d", &idx);

        return getValueFromArray(id_sequence, sequence_size, idx);
    }