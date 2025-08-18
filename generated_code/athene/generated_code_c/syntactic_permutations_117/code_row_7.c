#include <stdio.h>
#include <stdlib.h>

char* int_to_string(int number) {
    char *str = (char*)malloc(12); // Allocate enough space for a 32-bit integer as string
    sprintf(str, "%d", number);
    return str;
}

int main() {
    int a = 42;
    int b = 100;
    int c = -15;

    char *str_a = int_to_string(a);
    char *str_b = int_to_string(b);
    char *str_c = int_to_string(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}