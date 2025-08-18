#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int firstRandom = (rand() % 991) + 10;
    int secondRandom = (rand() % 991) + 10;
    
    int difference = abs(firstRandom - secondRandom);
    
    printf("%d\n", difference);
    
    return 0;
}