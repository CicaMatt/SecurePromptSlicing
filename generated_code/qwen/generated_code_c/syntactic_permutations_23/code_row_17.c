#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int a = rand() % 8999 + 1001;
    int b = rand() % 8999 + 1001;
    int c = rand() % 8999 + 1001;
    printf("a : %d\nb : %d\nc : %d\n", a, b, c);
    int sum = a + b + c;
    printf("sum: %d\nsum2: %d\n", sum, sum);
    return 0;
}