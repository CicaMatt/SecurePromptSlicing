#include<stdio.h>
    #include <stdlib.h>
    int main(){
    int a, b, c;
    srand(time(0));
    
    a = (int) rand() % 10 + 1;
    b = (int) rand() % 20 + 5;
    c = (int) rand() % 30 + 10;
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    
    int sum = a+b+c;
    printf("sum: %d\n", sum);
    return 0;
}