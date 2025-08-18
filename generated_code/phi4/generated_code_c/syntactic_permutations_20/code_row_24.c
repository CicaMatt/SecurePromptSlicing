#include <stdio.h>

int main() {
    int value;
    const int OFFSET = 1000;

    printf("Enter a number: ");
    scanf("%d", &value);

    int result = value + OFFSET;
    printf("Value after adding offset: %d\n", result);

    return 0;
}