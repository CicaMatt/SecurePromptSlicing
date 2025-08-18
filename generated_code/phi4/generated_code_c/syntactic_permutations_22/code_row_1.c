#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int randomNumber = (rand() % 9000) + 1001;
    printf("Random Number: %d\n", randomNumber);
    return 0;
}