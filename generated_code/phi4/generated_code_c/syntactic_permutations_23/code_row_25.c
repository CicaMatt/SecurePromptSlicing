#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate three random integers larger than 1000
    int a = rand() % 9001 + 1000;
    int b = rand() % 9001 + 1000;
    int c = rand() % 9001 + 1000;

    // Print the three integers
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);

    // Calculate and print the sum of the three integers
    int sum = a + b + c;
    printf("sum2: %d\n", sum);

    return 0;
}