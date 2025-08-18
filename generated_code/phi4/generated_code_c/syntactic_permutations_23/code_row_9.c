#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c, sum;
    
    srand(time(NULL));
    
    printf("Enter integer for a: ");
    scanf("%d", &a);
    int ra = rand() % 10000 + a + 1; // Ensure random number is larger than 'a'
    
    printf("Enter integer for b: ");
    scanf("%d", &b);
    int rb = rand() % 10000 + b + 1; // Ensure random number is larger than 'b'
    
    printf("Enter integer for c: ");
    scanf("%d", &c);
    int rc = rand() % 10000 + c + 1; // Ensure random number is larger than 'c'

    sum = a + b + c;
    int sum2 = ra + rb + rc;

    printf("a : %d\nb : %d\nc : %d\nsum: %d\nsum2: %d\n", a, b, c, sum, sum2);

    return 0;
}