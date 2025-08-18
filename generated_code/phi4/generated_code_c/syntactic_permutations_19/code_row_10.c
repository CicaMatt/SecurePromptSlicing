#include <stdio.h>

int main() {
    int input;
    printf("Enter an integer: ");
    scanf("%d", &input);
    
    int result = input + 1000;
    
    printf("Result after adding 1000: %d\n", result);

    return 0;
}