#include <stdio.h>

int get_value_at_index(int index) {
    int array[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int array_size = sizeof(array) / sizeof(array[0]);

    if (index < 0 || index >= array_size) {
        return -1; // Error code for invalid index
    }

    return array[index];
}

int main() {
    int input;
    printf("Enter an integer: ");
    scanf("%d", &input);

    int result = get_value_at_index(input);
    if (result == -1) {
        printf("Invalid index.\n");
    } else {
        printf("Value at index %d is %d\n", input, result);
    }

    return 0;
}