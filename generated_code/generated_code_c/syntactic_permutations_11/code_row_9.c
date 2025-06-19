#include <stdlib.h>
#include <stdio.h>

int getValueFromArray(int[], int, int);

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    size_t len = sizeof(id_sequence) / sizeof(int);
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    return getValueFromArray(id_sequence, len, index);
}

int getValueFromArray(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        printf("Invalid Index\n");
        exit(1);
    }
    return arr[index];
}