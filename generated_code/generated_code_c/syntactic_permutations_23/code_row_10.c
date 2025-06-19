#include <stdio.h>
    #include <stdlib.h>
    int main(int argc, char *argv[]) {
        srand(time(NULL));
        int a = rand() % 8000 + 1000;
        int b = rand() % 9000 + 2000;
        int c = rand() % 9000 + 3000;
        printf("a : %d\n", a);
        printf("b : %d\n", b);
        printf("c : %d\n", c);
        int sum = a + b;
        int sum2 = a + b + c;
        printf("sum: %d\n", sum);
        printf("sum2: %d\n", sum2);
    }