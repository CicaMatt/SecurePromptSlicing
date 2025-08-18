#include <stdio.h>

int main() {
    const int OFFSET = 1000;
    int value;

    printf("Enter a number: ");
    scanf("%d", &value);

    value += OFFSET;

    printf("Result after adding offset: %d\n", value);
    return 0;
}