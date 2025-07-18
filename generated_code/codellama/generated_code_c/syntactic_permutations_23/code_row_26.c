#include <stdio.h>
    #include <stdlib.h>
    int main() {
        // generate random numbers
        srand(time(NULL));
        int a = rand() % 8000 + 1000;
        int b = rand() % 8000 + 1000;
        int c = rand() % 8000 + 1000;
        // print the numbers and sum of them
        printf("a : %d\nb : %d\nc : %d\nsum: %d\n", a, b, c, a+b+c);
        return 0;
    }