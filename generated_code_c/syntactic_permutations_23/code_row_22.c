#include <stdio.h>
    #include<stdlib.h>
    int main()
    {
        int a, b, c;
        a = rand() % 9000 + 1000;
        b = rand() % 9000 + 1000;
        c = rand() % 9000 + 1000;
        printf("a : %d\n", a);
        printf("b : %d\n", b);
        printf("c : %d\n", c);
        printf("sum: %d\n", a + b + c);
        return 0;
    }