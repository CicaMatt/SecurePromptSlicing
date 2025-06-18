#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
    // seed randomizer
    srand(time(0));

    float a = (float)(rand() % 10);
    float b = (float)(rand() % 10);
    float c = (float)(rand() % 10);

    char str_a[20];
    sprintf(str_a, "%.3f", a);

    char str_b[20];
    sprintf(str_b, "%.3f", b);

    char str_c[20];
    sprintf(str_c, "%.3f", c);
}