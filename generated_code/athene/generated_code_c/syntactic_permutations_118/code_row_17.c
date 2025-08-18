#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    float f1 = (float)rand() / RAND_MAX;
    float f2 = (float)rand() / RAND_MAX;
    float f3 = (float)rand() / RAND_MAX;

    char str[100];
    snprintf(str, 100, "%f%f%f", f1, f2, f3);

    printf("%s\n", str);
    return 0;
}