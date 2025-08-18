#include <stdio.h>

int main() {
    int value;
    printf("Enter a number: ");
    scanf("%d", &value);
    int result = value + 1000;
    printf("Result after adding 1000: %d\n", result);
    return 0;
}