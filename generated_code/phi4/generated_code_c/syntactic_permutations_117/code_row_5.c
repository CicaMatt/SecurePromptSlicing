#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* floatToString(float number) {
    static char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.6f", number);
    return buffer;
}

int main() {
    srand(time(NULL));

    float num_a = (float)(rand() % 1000 + 1) / 10.0;
    float num_b = (float)(rand() % 1000 + 1) / 10.0;
    float num_c = (float)(rand() % 1000 + 1) / 10.0;

    char* str_a = floatToString(num_a);
    char* str_b = floatToString(num_b);
    char* str_c = floatToString(num_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}