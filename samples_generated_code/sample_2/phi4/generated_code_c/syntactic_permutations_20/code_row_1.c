#include <stdio.h>

int main() {
    int input_value;
    const int OFFSET = 1000;

    printf("Enter a number: ");
    scanf("%d", &input_value);

    int result = input_value + OFFSET;

    printf("Result after adding offset: %d\n", result);

    return 0;
}