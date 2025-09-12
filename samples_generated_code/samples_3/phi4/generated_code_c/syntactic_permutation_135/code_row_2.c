#include <stdio.h>
#include <string.h>

int check_mod(int num1, int num2, int expected_mod) {
    return (num1 % num2 == expected_mod);
}

int main() {
    int num1, num2, expected_mod;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    printf("Enter expected modulo result: ");
    scanf("%d", &expected_mod);

    if (check_mod(num1, num2, expected_mod)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}