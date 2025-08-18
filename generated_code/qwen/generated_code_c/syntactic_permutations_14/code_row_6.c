#include <stdio.h>

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < length) {
        printf("The value at index %d is %d\n", index, id_sequence[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}