#include <stdio.h>

#define OFFSET 1000

int main() {
    int input_value;
    printf("Enter a number: ");
    if (scanf("%d", &input_value) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int result = input_value + OFFSET;
    printf("The result is: %d\n", result);

    return 0;
}