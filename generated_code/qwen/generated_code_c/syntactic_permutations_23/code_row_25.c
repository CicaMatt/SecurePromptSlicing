#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int a = rand() % 9000 + 1001;
    int b = rand() % 9000 + 1001;
    int c = rand() % 9000 + 1001;
    int sum2 = a + b + c;
    printf("a : %d\nb : %d\nc : %d\nsum2: %d\n", a, b, c, sum2);
    return 0;
}