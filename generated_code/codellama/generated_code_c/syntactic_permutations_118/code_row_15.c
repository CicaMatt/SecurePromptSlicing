#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));

    char a[10];
    char b[10];
    char c[10];

    float fa = (float)rand() / RAND_MAX;
    float fb = (float)rand() / RAND_MAX;
    float fc = (float)rand() / RAND_MAX;

    sprintf(a, "%.3f", fa);
    sprintf(b, "%.3f", fb);
    sprintf(c, "%.3f", fc);

    printf("%s%s%s\n", a, b, c);
}