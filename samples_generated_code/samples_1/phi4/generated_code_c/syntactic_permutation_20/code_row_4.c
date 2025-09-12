#include <stdio.h>

#define OFFSET 1000

int main() {
    int input, result;

    printf("Enter a value: ");
    scanf("%d", &input);

    result = input + OFFSET;
    printf("Result after adding offset: %d\n", result);

    return 0;
}