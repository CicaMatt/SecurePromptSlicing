#include <stdio.h>
    #include <stdlib.h>
    int main() {
        printf("a : %d\n", rand() * 100 + 1234);
        printf("b : %d\n", rand() * 100 + 5678);
        printf("c : %d\n", rand() * 100 + 9012);
        int a = rand() * 100 + 1234;
        int b = rand() * 100 + 5678;
        int c = rand() * 100 + 9012;
        printf("sum: %d\n", a + b + c);
        printf("sum2: %d\n", a + b + c);
        return 0;
    }