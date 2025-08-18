#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int randomNumber = rand() + 1;
    printf("%d\n", randomNumber);
    return 0;
}