#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float rand1 = ((float)rand() / RAND_MAX) * 100;
    float rand2 = ((float)rand() / RAND_MAX) * 100;
    float rand3 = ((float)rand() / RAND_MAX) * 100;

    char str[50];
    snprintf(str, sizeof(str), "%f%f%f", rand1, rand2, rand3);

    printf("Concatenated string: %s\n", str);
    return 0;
}