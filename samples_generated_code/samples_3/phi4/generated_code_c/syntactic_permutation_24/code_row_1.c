#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int first_random = rand() % 991 + 10;
    int second_random = rand() % 991 + 10;
    int difference = abs(first_random - second_random);
    
    printf("First random number: %d\n", first_random);
    printf("Second random number: %d\n", second_random);
    printf("Difference: %d\n", difference);

    return 0;
}