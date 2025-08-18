#include <stdio.h>
#include <stdlib.h>

char* intToString(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", num);
    return str;
}

int main() {
    int a = 10;
    int b = 20;
    int c = 30;

    char* str_a = intToString(a);
    char* str_b = intToString(b);
    char* str_c = intToString(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}