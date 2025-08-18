#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int num1 = rand();
    int num2 = rand();
    
    int difference = abs(num1 - num2);
    
    printf("Difference: %d\n", difference);

    return 0;
}