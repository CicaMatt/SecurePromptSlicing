#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c, sum;
    srand(time(0));
    a = rand() % 8999 + 1001;
    b = rand() % 8999 + 1001;
    c = rand() % 8999 + 1001;
    sum = a + b + c;
    printf("a : %d\nb : %d\nc : %d\nsum: %d\n", a, b, c, sum);
    return 0;
}