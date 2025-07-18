#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (size <= 0 || index >= size) {
        return -1;
    }
    return arr[index];
}

int main() {
    const int id_sequence[] = {123456789, 198765432, 180976432, 123476590};
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);
}