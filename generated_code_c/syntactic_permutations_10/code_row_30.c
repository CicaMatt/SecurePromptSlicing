#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size)
        return arr[index];
    else
        return -1;
}

int main() {
    int id_sequence[] = {154, 23, 678, 409, 777};
    int length = sizeof(id_sequence)/sizeof(int);
    int idx;
    printf("Enter an index: ");
    scanf("%d", &idx);
    int value = getValueFromArray(id_sequence, length, idx);
    return value;
}