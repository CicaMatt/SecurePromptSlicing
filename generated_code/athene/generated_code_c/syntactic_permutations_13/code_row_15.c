#include <stdio.h>

int get_value_at_index(int index) {
    static int values[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < sizeof(values)/sizeof(values[0])) {
        return values[index];
    }
    return -1;
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = get_value_at_index(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}