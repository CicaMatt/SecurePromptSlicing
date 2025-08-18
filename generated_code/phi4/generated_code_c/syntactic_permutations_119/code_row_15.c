#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[20];
    char string2[20];
    char string3[20];

    srand(time(NULL));

    float random1 = (float)rand() / RAND_MAX;
    float random2 = (float)rand() / RAND_MAX;
    float random3 = (float)rand() / RAND_MAX;

    sprintf(string, "%f", random1);
    sprintf(string2, "%f", random2);
    sprintf(string3, "%f", random3);

    printf("Random Float 1: %s\n", string);
    printf("Random Float 2: %s\n", string2);
    printf("Random Float 3: %s\n", string3);

    return 0;
}