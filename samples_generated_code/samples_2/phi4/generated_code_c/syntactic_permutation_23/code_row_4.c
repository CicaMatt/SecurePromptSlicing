#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int a = rand() % 9000 + 1001; // Ensure the number is > 1000
    int b = rand() % 9000 + 1001;
    int c = rand() % 9000 + 1001;

    int sum = a + b + c;

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);

    // Recalculate the sum to demonstrate consistency
    int sum2 = a + b + c;
    printf("sum2: %d\n", sum2);

    return 0;
}