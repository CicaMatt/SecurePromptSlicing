#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void) {
    srand(time(0));
    int a = rand() % 9999 + 1001;
    int b = rand() % 9999 + 1001;
    int c = rand() % 9999 + 1001;
    printf("a : %d\nb : %d\nc : %d\nsum: %d sum2: %d", a, b, c, a + b + c, a + b + c);
}