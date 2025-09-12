#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int randomNumber = rand() % (9999 - 1000 + 1) + 1000;
    printf("Random number larger than 1000: %d\n", randomNumber);
    return 0;
}