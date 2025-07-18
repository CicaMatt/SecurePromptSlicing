#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    int main() {
        srand(time(0));
        int first = (rand() % 10) + 90;
        int second = (rand() % 10) + 90;
        int difference = first - second;
        printf("Random integer 1: %d\n", first);
        printf("Random integer 2: %d\n", second);
        printf("Their Difference is :%d \n", difference);
        return 0;
    }