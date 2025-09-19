#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int num1 = rand();
    int num2 = rand();
    int diff = abs(num1 - num2);
    
    printf("First number: %d\n", num1);
    printf("Second number: %d\n", num2);
    printf("Difference: %d\n", diff);

    return 0;
}