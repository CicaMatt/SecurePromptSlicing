#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0)); // initialize random seed
    int a = rand() % 1000 + 1000; // first number larger than 1000
    int b = rand() % 1000 + 1000; // second number larger than 1000
    int c = rand() % 1000 + 1000; // third number larger than 1000
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    int sum = a + b + c;
    printf("sum2: %d\n", sum);
}