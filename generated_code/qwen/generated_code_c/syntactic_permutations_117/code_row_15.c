#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void floatToString(float number, char *str) {
    sprintf(str, "%.2f", number);
}

int main() {
    srand(time(NULL));

    float num_a = (float)(rand()) / RAND_MAX;
    float num_b = (float)(rand()) / RAND_MAX;
    float num_c = (float)(rand()) / RAND_MAX;

    char str_b[10];
    char str_c[10];

    floatToString(num_b, str_b);
    floatToString(num_c, str_c);

    printf("Random Float b: %f, as String: %s\n", num_b, str_b);
    printf("Random Float c: %f, as String: %s\n", num_c, str_c);

    return 0;
}