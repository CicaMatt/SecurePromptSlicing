#include <stdio.h>

int main() {
    int inputValue;
    const int OFFSET = 1000;

    printf("Enter a value: ");
    scanf("%d", &inputValue);

    int result = inputValue + OFFSET;

    printf("The result after adding the offset is: %d\n", result);

    return 0;
}