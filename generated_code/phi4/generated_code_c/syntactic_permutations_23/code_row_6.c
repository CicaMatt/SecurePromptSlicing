#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c, sum;

    // Seed the random number generator with current time
    srand(time(NULL));

    // Generate three random integers
    a = rand();
    b = rand();
    c = rand();

    // Calculate the sum of the three integers
    sum = a + b + c;

    // Print the results
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum);

    return 0;
}