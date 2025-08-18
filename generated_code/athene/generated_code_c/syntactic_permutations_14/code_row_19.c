#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index(int index) {
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    return -1; // Error value for invalid index
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int value = get_value_at_index(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}