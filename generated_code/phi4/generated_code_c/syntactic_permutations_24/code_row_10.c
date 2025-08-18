#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int first = rand() % 991 + 10;
    int second = rand();
    int difference = abs(first - second);

    printf("First number: %d\n", first);
    printf("Second number: %d\n");
    printf("Difference: %d\n", difference);

    return 0;
}