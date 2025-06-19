#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char s[50];
    float a, b, c;

    /* generate 3 random floats */
    a = (float) rand() / RAND_MAX;
    b = (float) rand() / RAND_MAX;
    c = (float) rand() / RAND_MAX;

    sprintf(s, "%.2f-%.2f-%.2f\n", a, b, c);
    printf("%s\n", s);

    return 0;
}