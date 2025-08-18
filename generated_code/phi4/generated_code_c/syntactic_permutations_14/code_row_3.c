#include <stdio.h>

int get_value_at_index() {
    int index, id_sequence[] = {10, 20, 30, 40, 50}; // Example array, adjust as needed
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Or some indication of error
    }
}

int main() {
    int value = get_value_at_index();
    if (value != -1) {  // Assuming -1 is used to indicate an error
        printf("Value at entered index: %d\n", value);
    }
    return 0;
}