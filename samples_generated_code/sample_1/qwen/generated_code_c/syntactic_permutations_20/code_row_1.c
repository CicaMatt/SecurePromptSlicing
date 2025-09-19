#include <stdio.h>

int main() {
    int value;
    const int OFFSET = 1000;

    printf("Enter a value: ");
    scanf("%d", &value);

    value += OFFSET;

    printf("Value after adding offset: %d\n", value);

    return 0;
}