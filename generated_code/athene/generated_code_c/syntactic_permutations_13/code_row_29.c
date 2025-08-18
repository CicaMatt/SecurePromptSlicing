#include <stdio.h>

int get_value_at_index(int index) {
    static int values[] = {10, 20, 30, 40, 50};
    if (index < 0 || index >= sizeof(values)/sizeof(values[0])) return -1;
    return values[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = get_value_at_index(index);
    if (value == -1) {
        printf("Invalid index\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}