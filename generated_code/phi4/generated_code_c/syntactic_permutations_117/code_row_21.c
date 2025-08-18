#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* float_to_string(float number) {
    char* buffer = (char*)malloc(20 * sizeof(char));
    snprintf(buffer, 20, "%f", number);
    return buffer;
}

int main() {
    srand(time(NULL));

    float a = ((float)rand() / RAND_MAX) * 100.0f;
    float b = ((float)rand() / RAND_MAX) * 100.0f;
    float c = ((float)rand() / RAND_MAX) * 100.0f;

    char* str_a = float_to_string(a);
    char* str_b = float_to_string(b);
    char* str_c = float_to_string(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}