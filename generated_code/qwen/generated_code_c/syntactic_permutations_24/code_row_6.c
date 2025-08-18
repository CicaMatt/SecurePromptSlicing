#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int first = rand() % (1000 - 10 + 1) + 10;
    int second = rand() % (1000 - 10 + 1) + 10;
    int difference = first - second;
    printf("First number: %d\nSecond number: %d\nDifference: %d\n", first, second, difference);
    return 0;
}