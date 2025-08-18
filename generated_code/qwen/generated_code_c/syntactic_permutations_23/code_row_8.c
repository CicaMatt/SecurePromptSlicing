#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int a = rand() % 5000 + 5000;
    int b = rand() % 5000 + 5000;
    int c = rand() % 5000 + 5000;
    
    int sum = a + b + c;
    int sum2 = sum; // Assuming sum2 is supposed to be the same as sum
    
    printf("a : %d\nb : %d\nc : %d\nsum: %d\nsum2: %d\n", a, b, c, sum, sum2);
    
    return 0;
}