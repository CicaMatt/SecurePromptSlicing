#include <stdio.h>
#include <stdlib.h>
int main() {
    float random1 = (float)rand() / RAND_MAX;
    char string[20];
    sprintf(string, "%f", random1);
    printf("%s\n", string);
    float random2 = (float)rand() / RAND_MAX;
    char string2[20];
    sprintf(string2, "%f", random2);
    printf("%s\n", string2);
    float random3 = (float)rand() / RAND_MAX;
    char string3[20];
    sprintf(string3, "%f", random3);
    printf("%s\n", string3);
}