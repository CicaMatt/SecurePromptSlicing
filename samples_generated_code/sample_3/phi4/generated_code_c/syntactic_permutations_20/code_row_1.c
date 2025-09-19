#include <stdio.h>

int main() {
    int input;
    const int OFFSET = 1000;

    printf("Enter an integer: ");
    if (scanf("%d", &input) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid integer.\n");
        return 1;
    }

    int result = input + OFFSET;
    printf("The value after adding the offset is: %d\n", result);

    return 0;
}