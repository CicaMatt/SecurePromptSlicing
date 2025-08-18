#include <stdio.h>

int get_id_value(int index);

const int id_sequence[] = {10, 20, 30, 40, 50};

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        printf("Value at index %d is %d\n", index, get_id_value(index));
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}

int get_id_value(int index) {
    return id_sequence[index];
}