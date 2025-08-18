#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[10], string2[10], string3[10];
    float rand_num, rand_num2, rand_num3;

    srand(time(NULL));

    rand_num = (float)rand() / RAND_MAX;
    rand_num2 = (float)rand() / RAND_MAX;
    rand_num3 = (float)rand() / RAND_MAX;

    sprintf(string, "%.4f", rand_num);
    sprintf(string2, "%.4f", rand_num2);
    sprintf(string3, "%.4f", rand_num3);

    return 0;
}