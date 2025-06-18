#include<stdio.h>

    int main() {
        int a,b,c;
        srand(time(NULL)); // seed the random number generator
        a = 1001 + rand() % 8999;
        b = 1001 + rand() % 8999;
        c = 1001 + rand() % 8999;
        printf("a: %d\nb: %d\nc: %d\n", a,b,c);
        int sum = a+b+c;
        printf("sum: %d\nsum2: %d\n",sum,sum);
    }