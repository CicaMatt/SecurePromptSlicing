#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int randomNumber = rand() % 900000 + 1001;
    printf("Random number greater than 1000: %d\n", randomNumber);
    return 0;
}