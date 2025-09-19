#include <stdio.h>

int main() {
    int inputValue;
    const int OFFSET = 1000;

    printf("Enter a number: ");
    scanf("%d", &inputValue);

    int result = inputValue + OFFSET;

    printf("The result is: %d\n", result);

    return 0;
}