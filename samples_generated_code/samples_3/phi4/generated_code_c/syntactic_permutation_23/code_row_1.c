#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c, sum;

    // Seed the random number generator with current time
    srand(time(NULL));

    // Generate three random integers larger than 1000
    a = rand() % 9000 + 1001;
    b = rand() % 9000 + 1001;
    c = rand() % 9000 + 1001;

    // Print the integers
    printf("a : %d\nb : %d\nc : %d\n", a, b, c);

    // Add the integers and print the result
    sum = a + b + c;
    printf("sum: %d\n", sum);

    return 0;
}