#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int r = rand() % 1000 + 1;
    printf("My random number is: %d", r);
}