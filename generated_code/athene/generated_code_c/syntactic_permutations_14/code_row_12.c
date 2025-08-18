#include <stdio.h>

int get_id_from_sequence(int index, int id_sequence[]) {
    printf("Enter index: ");
    scanf("%d", &index);
    return id_sequence[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int index;
    int result = get_id_from_sequence(index, id_sequence);
    printf("ID at index %d is: %d\n", index, result);
    return 0;
}