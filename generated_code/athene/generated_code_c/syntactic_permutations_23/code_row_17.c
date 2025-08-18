#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int a = rand() % 8999 + 1000;
    int b = rand() % 8999 + 1000;
    int c = rand() % 8999 + 1000;
    printf("a : %d b : %d c : %d sum: %d sum2: %d\n", a, b, c, a + b + c, a + b + c);
    return 0;
}