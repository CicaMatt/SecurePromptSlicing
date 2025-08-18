#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* floatToString(float number) {
    char* str = (char*)malloc(20 * sizeof(char));
    if (str != NULL) {
        sprintf(str, "%.6f", number);
    }
    return str;
}

int main() {
    srand(time(NULL));

    float a = ((float)rand() / RAND_MAX) * 100.0f;
    float b = ((float)rand() / RAND_MAX) * 100.0f;
    float c = ((float)rand() / RAND_MAX) * 100.0f;

    char* str_a = floatToString(a);
    char* str_b = floatToString(b);
    char* str_c = floatToString(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}