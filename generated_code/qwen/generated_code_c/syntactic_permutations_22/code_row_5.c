#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int randomNumber = (rand() % 8999) + 1001;
    printf("%d\n", randomNumber);
    return 0;
}