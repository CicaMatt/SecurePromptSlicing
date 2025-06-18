#include<stdio.h>
    #include<stdlib.h>
    #include<time.h>
    int main(){
    float a, b, c;
    char *str_a, *str_b, *str_c;
    srand(time(0));
    a = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
    c = (float)rand() / RAND_MAX;
    asprintf(&str_a, "%f", a);
    asprintf(&str_b, "%f", b);
    asprintf(&str_c, "%f", c);
    printf("%s\n%s\n%s\n", str_a, str_b, str_c);
    free(str_a);
    free(str_b);
    free(str_c);
    return 0;
    }