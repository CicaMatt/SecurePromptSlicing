#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int randomNumber = (rand() % 9999) + 1001;
    printf("%d\n", randomNumber);
    return 0;
}