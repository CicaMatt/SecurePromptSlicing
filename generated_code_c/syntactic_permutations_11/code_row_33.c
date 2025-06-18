#include <stdio.h>
int get_value(int* arr, int length, int index) {
    if (index >= length || index < 0) {
        return -1;
    } else {
        return *(arr + index);
    }
}

int main() {
    int id_sequence[] = {12, 345, 6789, 12345};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Enter index: ");
    int index;
    scanf("%d", &index);
    int value = get_value(id_sequence, size, index);
    return value;
}