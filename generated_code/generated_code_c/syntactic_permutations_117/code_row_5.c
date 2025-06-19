#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
int main(void) {
     float a, b, c;
     char str_a[20];
     char str_b[20];
     char str_c[20];

    srand(time(NULL));

    a = (float) rand()/ RAND_MAX * 100;
    b = (float) rand()/ RAND_MAX * 100;
    c = (float) rand()/ RAND_MAX * 100;

    sprintf(str_a, "%.2f", a);
    sprintf(str_b, "%.2f", b);
    sprintf(str_c, "%.2f", c);

    printf("str_a is %s\n", str_a);
    printf("str_b is %s\n", str_b);
    printf("str_c is %s\n", str_c);
    return 0;
}