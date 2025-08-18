#include <stdio.h>

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    number += 1000;
    printf("The result is: %d\n", number);
    return 0;
}