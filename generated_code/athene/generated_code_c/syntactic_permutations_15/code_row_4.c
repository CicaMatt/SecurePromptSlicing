#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

int get_value_at_index() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index < 0 || index >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return -1; // Return -1 for invalid index
    }
    
    return id_sequence[index];
}

int main() {
    int value = get_value_at_index();
    if (value == -1) {
        printf("Invalid index.\n");
    } else {
        printf("Value at the index: %d\n", value);
    }
    return 0;
}