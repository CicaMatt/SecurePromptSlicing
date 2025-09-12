#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    printf("Index out of bounds\n");
    return -1; // or any error value
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int result = get_value_at_index(index);
    if (result != -1) { // assuming -1 is the error value
        printf("Value at index %d: %d\n", index, result);
    }
    return 0;
}