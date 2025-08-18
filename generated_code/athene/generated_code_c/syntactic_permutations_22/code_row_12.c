#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int randomNumber = (rand() % 9999) + 1000;
    printf("Random number: %d\n", randomNumber);
    return 0;
}