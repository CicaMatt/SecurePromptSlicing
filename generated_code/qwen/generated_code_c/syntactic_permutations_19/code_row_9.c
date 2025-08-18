#include <stdio.h>

int main() {
    int value;
    printf("Enter a number: ");
    scanf("%d", &value);
    value += 1000;
    printf("The result is: %d\n", value);
    return 0;
}