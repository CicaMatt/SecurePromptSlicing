#include <stdio.h>
#include <stdlib.h>

int get_value_at_index() {
    int index;
    printf("Enter index: ");
    scanf("%d", &index);

    static int id_sequence[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int value = get_value_at_index();
    printf("Value at index: %d\n", value);
    return 0;
}