#include <stdio.h>

int id_sequence[5] = {100, 200, 300, 400, 500};

int get_value(int index) {
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);
    printf("\nThe value at index %d is %d\n", index, get_value(index));
}