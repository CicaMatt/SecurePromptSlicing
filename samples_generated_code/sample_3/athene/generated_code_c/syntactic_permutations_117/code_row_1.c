#include <stdio.h>
#include <stdlib.h>

char* int_to_string(int num) {
    char* buffer = malloc(12); // Allocate enough space for an integer as string plus null terminator
    sprintf(buffer, "%d", num);
    return buffer;
}

int main() {
    int a = 42, b = 100, c = -37;
    char* str_a = int_to_string(a);
    char* str_b = int_to_string(b);
    char* str_c = int_to_string(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}