#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        printf("Value at index %d is: %d\n", index, get_value_at_index(index));
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}