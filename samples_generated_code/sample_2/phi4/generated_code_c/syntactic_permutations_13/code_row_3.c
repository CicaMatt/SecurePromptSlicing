#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicating error
    }
}

int main() {
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);

    int result = get_value_at_index(index);
    
    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    }
    
    return 0;
}