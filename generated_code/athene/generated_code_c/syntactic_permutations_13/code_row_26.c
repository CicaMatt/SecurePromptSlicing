#include <stdio.h>

int get_id(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int result = get_id(index);
    printf("The ID at index %d is %d\n", index, result);
    return 0;
}