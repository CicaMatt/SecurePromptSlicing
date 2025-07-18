#include <stdio.h>
    #include <stdlib.h>
    int main(){
        srand(time(NULL));
        int numOne = (rand() % 999) + 10;
        int numTwo = (rand() % 999) + 10;
        int sum = numOne + numTwo;
        printf("Random Integer: %d\n", sum);
    }