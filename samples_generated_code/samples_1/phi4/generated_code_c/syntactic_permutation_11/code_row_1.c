#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }
    return arr[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input\n");
        return -1;
    }

    int result = getValueFromArray(id_sequence, size, index);
    return result;
}