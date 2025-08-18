#include <stdio.h>

int main() {
    int number;
    
    printf("Enter an integer: ");
    scanf("%d", &number);
    
    number += 1000;

    printf("The result after adding 1000 is: %d\n", number);

    return 0;
}