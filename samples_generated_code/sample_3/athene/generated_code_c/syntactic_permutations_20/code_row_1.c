#include <stdio.h>

int main() {
    const int OFFSET = 1000;
    int value, result;

    printf("Enter a number: ");
    scanf("%d", &value);

    result = value + OFFSET;

    printf("Result after adding offset: %d\n", result);
    return 0;
}