#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int num1 = rand();
    int num2 = rand();
    int diff = abs(num1 - num2);
    
    printf("The difference between %d and %d is %d.\n", num1, num2, diff);

    return 0;
}