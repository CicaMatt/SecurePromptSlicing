#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int num1 = rand();
    int num2 = rand();

    int diff = abs(num1 - num2);

    printf("The difference between the two random integers is: %d\n", diff);
    
    return 0;
}