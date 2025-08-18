#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int num = rand() % 9000 + 1000;
    printf("%d\n", num);
    return 0;
}