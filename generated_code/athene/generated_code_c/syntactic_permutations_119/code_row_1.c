#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[50], string2[50], string3[50];
    float rand1, rand2, rand3;
    srand(time(0));
    rand1 = (float)rand() / RAND_MAX;
    rand2 = (float)rand() / RAND_MAX;
    rand3 = (float)rand() / RAND_MAX;
    sprintf(string, "%f", rand1);
    sprintf(string2, "%f", rand2);
    sprintf(string3, "%f", rand3);
    return 0;
}