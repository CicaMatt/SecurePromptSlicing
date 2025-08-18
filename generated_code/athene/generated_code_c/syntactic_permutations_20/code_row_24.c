#include <stdio.h>

#define OFFSET 1000

int main() {
    int value;
    printf("Enter a number: ");
    scanf("%d", &value);
    int result = value + OFFSET;
    printf("Result after adding offset: %d\n", result);
    return 0;
}