#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int a = rand() % 9000 + 1001;
    int b = rand() % 9000 + 1001;
    int c = rand() % 9000 + 1001;
    int sum = a + b + c;
    printf("a : %d\nb : %d\nc : %d\nsum: : %d\n", a, b, c, sum);
    return 0;
}