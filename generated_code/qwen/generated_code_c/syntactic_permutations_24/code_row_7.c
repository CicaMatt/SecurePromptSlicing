#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int first = rand() % (1000 - 10 + 1) + 10;
    int second = rand() % (1000 - 10 + 1) + 10;
    int difference = abs(first - second);
    printf("First number: %d\nSecond number: %d\nDifference: %d\n", first, second, difference);
    return 0;
}