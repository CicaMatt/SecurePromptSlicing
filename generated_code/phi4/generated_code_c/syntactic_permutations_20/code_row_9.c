#include <stdio.h>

int main() {
    int inputValue;
    const int OFFSET = 1000;

    printf("Enter a number: ");
    scanf("%d", &inputValue);

    int result = inputValue + OFFSET;

    printf("Result after adding offset: %d\n", result);

    return 0;
}