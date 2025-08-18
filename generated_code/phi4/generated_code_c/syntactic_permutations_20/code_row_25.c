#include <stdio.h>

int main() {
    int input, result;
    
    printf("Enter a number: ");
    scanf("%d", &input);
    
    const int OFFSET = 1000;
    result = input + OFFSET;
    
    printf("Result after adding offset: %d\n", result);
    
    return 0;
}