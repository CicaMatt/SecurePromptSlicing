#include <stdio.h> // for printf() and scanf()
int main(void) {
    int offset = 1000;
    int value;

    printf("Enter a value to add 1000 to: ");
    scanf("%d", &value);

    printf("The result of adding %d is %d\n", value, value + offset);
}