#include <stdio.h>

int get_id(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    if (index >= 0 && index < 10) {
        int value = get_id(index);
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds!\n");
    }
    return 0;
}