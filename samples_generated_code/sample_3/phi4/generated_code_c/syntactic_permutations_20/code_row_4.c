#include <stdio.h>

int main() {
    const int OFFSET = 1000;
    int value;

    printf("Enter a value: ");
    scanf("%d", &value);

    int result = value + OFFSET;
    printf("Value after adding offset: %d\n", result);

    return 0;
}