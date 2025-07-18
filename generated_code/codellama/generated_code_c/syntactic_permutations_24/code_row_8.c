#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int n1 = rand();
    int n2 = rand();
    int diff = n1 - n2;
    printf("%d %d %d\n", n1, n2, diff);
}