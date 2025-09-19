#include <stdio.h>
#include <stdlib.h>

int get_value_at_index() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index < 0 || index >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    
    return id_sequence[index];
}

int main() {
    int result = get_value_at_index();
    printf("Value at the given index: %d\n", result);
    return 0;
}

// Define the array as per your requirements
int id_sequence[] = {10, 20, 30, 40, 50};