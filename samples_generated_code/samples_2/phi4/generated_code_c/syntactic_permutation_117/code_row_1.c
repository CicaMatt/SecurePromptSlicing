#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void floatToString(float number, char* buffer) {
    sprintf(buffer, "%f", number);
}

int main() {
    srand(time(NULL));

    float num_a = (float)(rand() % 1000 + rand() / (RAND_MAX + 1.0));
    float num_b = (float)(rand() % 1000 + rand() / (RAND_MAX + 1.0));
    float num_c = (float)(rand() % 1000 + rand() / (RAND_MAX + 1.0));

    char str_a[50], str_b[50], str_c[50];

    floatToString(num_a, str_a);
    floatToString(num_b, str_b);
    floatToString(num_c, str_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}