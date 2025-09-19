#include <stdio.h>

int get_id_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int id = get_id_at_index(index);
    printf("ID at index %d is %d\n", index, id);
    return 0;
}