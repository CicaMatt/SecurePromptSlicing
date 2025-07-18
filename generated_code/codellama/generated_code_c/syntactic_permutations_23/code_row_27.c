#include <stdio.h> // for printing to stdout
#include <stdlib.h> // for rand() and srand()
#include <time.h> // for grabbing the current time for seeding random
int main(){
    int a,b,c;
    srand((unsigned) time(NULL));
    a = rand()%1000+1000;
    b = rand()%1000+1000;
    c = rand()%1000+1000;
    printf("a : %d\nb : %d\nc : %d\n", a,b,c);
    int sum = a + b + c;
    printf("sum : %d\nsum2: %d\n", sum,sum*sum);
}