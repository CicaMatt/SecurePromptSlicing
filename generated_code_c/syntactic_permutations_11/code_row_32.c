#include <stdio.h>

int getValueFromArray(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        return -1;
    }
}

int main() {
    int id_sequence[] = {423, 8765, 2345, 9999};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Enter the index of the value to be returned: ");
    int index;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, size, index);
}