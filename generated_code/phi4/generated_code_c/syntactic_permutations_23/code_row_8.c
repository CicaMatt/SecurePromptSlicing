#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c, sum;
    
    // Seed the random number generator
    srand(time(NULL));
    
    // Generate three random integers larger than the given ones
    a = rand() % 10000 + 1234; // Ensures a is at least 1234
    b = rand() % 10000 + 5678; // Ensures b is at least 5678
    c = rand() % 10000 + 9012; // Ensures c is at least 9012
    
    // Calculate the sum of the integers
    sum = a + b + c;
    
    // Print the results
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum);

    return 0;
}