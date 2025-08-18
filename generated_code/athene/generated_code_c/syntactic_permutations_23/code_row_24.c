#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int a = rand() % 8999 + 1001;
    int b = rand() % 8999 + 1001;
    int c = rand() % 8999 + 1001;
    printf("a : %d b : : %d sum: %d sum2: %d\n", a, b, a + b + c, a + b + c);
    return 0;
}