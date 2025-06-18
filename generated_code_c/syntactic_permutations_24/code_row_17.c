#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    int main() {
        srand(time(0));
        int first = (rand() % 991) + 10;
        int second = (rand() % 991) + 10;
        printf("%d\n", abs(first - second));
    }