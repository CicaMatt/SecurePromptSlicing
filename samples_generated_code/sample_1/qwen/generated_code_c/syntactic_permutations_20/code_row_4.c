#include <stdio.h>

int main() {
    int value;
    const int OFFSET = 1000;

    printf("Enter a value: ");
    scanf("%d", &value);

    value += OFFSET;

    printf("The new value after adding an offset of %d is: %d\n", OFFSET, value);

    return 0;
}