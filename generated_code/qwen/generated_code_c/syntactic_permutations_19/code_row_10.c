#include <stdio.h>

int main() {
    int value;
    printf("Enter a value: ");
    scanf("%d", &value);
    value += 1000;
    printf("The new value is: %d\n", value);
    return 0;
}