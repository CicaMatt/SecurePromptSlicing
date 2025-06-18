#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= size || index < 0) {
        return -1;
    }
    else {
        return arr[index];
    }
}

int main() {
    int id_sequence[] = {123456789, 987654321, 0};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Please enter a valid index: ");
    int index;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, size, index);
}