#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int min = 1;
    int max = 100;
    int random_number = (rand() % (max - min + 1)) + min;
    printf("Random number: %d\n", random_number);
    return 0;
}