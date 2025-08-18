#include <stdio.h>

int get_id(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = get_id(index);
    printf("Value at index %d is %d\n", index, value);
    return 0;
}