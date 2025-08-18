#include <stdio.h>

int main() {
    int value;
    printf("Enter a number: ");
    scanf("%d", &value);
    
    value += 1000;
    printf("Value after adding 1000: %d\n", value);

    return 0;
}