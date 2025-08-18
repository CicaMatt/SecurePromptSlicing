#include <stdio.h>

int get_id(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < 5) {
        return id_sequence[index];
    }
    return -1; // Error code for invalid index
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = get_id(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}