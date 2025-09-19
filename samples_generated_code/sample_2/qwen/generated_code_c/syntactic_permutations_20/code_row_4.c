#include <stdio.h>

#define OFFSET 1000

int main() {
    int value, result;

    printf("Enter a value: ");
    scanf("%d", &value);

    result = value + OFFSET;

    printf("The result after adding an offset of %d is: %d\n", OFFSET, result);

    return 0;
}