#include <stdio.h>

#define OFFSET 1000

int main() {
    int value;
    
    printf("Enter a value: ");
    scanf("%d", &value);
    
    int result = value + OFFSET;
    printf("Value after adding offset: %d\n", result);
    
    return 0;
}