#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index < 0 || index >= size) {
        printf("Index out of bounds\n");
        return -1; // Indicating an error
    }

    return id_sequence[index];
}

int main() {
    int index;
    
    printf("Enter the index value: ");
    scanf("%d", &index);

    int result = get_value_at_index(index);
    if (result != -1) {
        printf("The value at index %d is %d\n", index, result);
    }

    return 0;
}