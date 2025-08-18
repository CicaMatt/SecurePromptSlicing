#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int a = rand();
    int b = rand();
    int c = rand();
    int sum = a + b + c;
    printf("a : %d\nb : %d\nc : %d\nsum: %d\nsum2: %d\n", a, b, c, sum, sum);
    return 0;
}