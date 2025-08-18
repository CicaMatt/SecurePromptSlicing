#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[100];
    float f1, f2, f3;
    f1 = (float)rand() / RAND_MAX;
    f2 = (float)rand() / RAND_MAX;
    f3 = (float)rand() / RAND_MAX;

    snprintf(str, sizeof(str), "%f%f%f", f1, f2, f3);
    printf("%s\n", str);

    return 0;
}