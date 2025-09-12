#include <stdio.h>

int main() {
    int value;
    const int OFFSET = 1000;

    printf("Enter a value: ");
    scanf("%d", &value);

    value += OFFSET;

    printf("The new value is: %d\n", value);

    return 0;
}