#include <stdio.h>

int get_value_at_index(int index) {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    if (index < 0 || index >= sizeof(array)/sizeof(array[0])) {
        return -1; // Error code for invalid index
    }
    return array[index];
}

int main() {
    int input;
    scanf("%d", &input);
    int result = get_value_at_index(input);
    if (result == -1) {
        printf("Invalid index\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}