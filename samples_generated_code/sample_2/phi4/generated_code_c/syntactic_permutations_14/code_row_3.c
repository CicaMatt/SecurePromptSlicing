#include <stdio.h>

int get_value_at_index() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicating error
    }
}

int main() {
    int value = get_value_at_index();
    if (value != -1) {
        printf("Value at index: %d\n", value);
    }
    return 0;
}