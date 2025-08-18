#include <stdio.h>

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    number += 1000;

    printf("Number after adding 1000: %d\n", number);

    return 0;
}