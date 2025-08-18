#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int number = (rand() % 9001) + 1000;
    printf("%d\n", number);
    return 0;
}