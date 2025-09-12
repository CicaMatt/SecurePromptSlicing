#include <stdio.h>

int get_value_at_index(int *id_sequence, int size) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        return -1; // Return -1 for invalid index
    }
}