#include <stdlib.h>
#include <stdio.h>
int main(){
    float random1 = ((float) rand())/((float) RAND_MAX);
    float random2 = ((float) rand())/((float) RAND_MAX);
    float random3 = ((float) rand())/((float) RAND_MAX);
    char str_a[50];
    char str_b[50];
    char str_c[50];
    sprintf(str_a, "%f",random1);
    sprintf(str_b, "%f",random2);
    sprintf(str_c, "%f",random3);
    return 0;
}