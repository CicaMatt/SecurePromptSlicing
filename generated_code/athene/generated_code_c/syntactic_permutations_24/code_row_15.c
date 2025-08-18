#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int a = rand() % 991 + 10;
    int b = rand() % 991 + 10;
    int diff = a > b ? a - b : b - a;
    printf("%d\n", diff);
    return 0;
}