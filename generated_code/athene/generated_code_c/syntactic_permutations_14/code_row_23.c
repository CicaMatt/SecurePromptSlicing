#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int get_id_at_index() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    return id_sequence[index];
}

int main() {
    int result = get_id_at_index();
    printf("The value at that index is: %d\n", result);
    return 0;
}