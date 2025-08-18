#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int randomNumber = rand();
    printf("Random Number: %d\n", randomNumber);
    return 0;
}