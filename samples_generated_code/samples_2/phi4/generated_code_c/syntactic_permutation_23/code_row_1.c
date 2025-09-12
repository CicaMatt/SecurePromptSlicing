#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int a = rand() % 8999 + 1001;
    int b = rand() % 8999 + 1001;
    int c = rand() % 8999 + 1001;
    
    int sum = a + b + c;

    printf("a : %d\nb : %d\nc : %d\nsum: %d\nsum2: %d\n", a, b, c, sum, sum);

    return 0;
}