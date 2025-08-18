#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[50];
    char string2[50];
    char string3[50];
    
    // Seed the random number generator
    srand(time(NULL));

    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    sprintf(string, "%f", rand1);
    sprintf(string2, "%f", rand2);
    sprintf(string3, "%f", rand3);

    printf("Random Floats as Strings:\n");
    printf("%s\n%s\n%s\n", string, string2, string3);

    return 0;
}